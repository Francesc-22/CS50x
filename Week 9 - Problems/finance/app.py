import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    stocks = db.execute("SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    stock_symbols = []
    shares = []
    current_price = []
    total_value = []
    balance = 0

    for stock in stocks:
        stock_data = lookup(stock["symbol"])

        stock_symbols.append(stock["symbol"])
        shares.append(stock["total_shares"])
        current_price.append(usd(stock_data["price"]))
        total_value.append(usd(stock_data["price"] * stock["total_shares"]))

        balance += stock_data["price"] * stock["total_shares"]

    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    balance += cash

    return render_template("index.html", stock=stock_symbols, shares=shares, current_price=current_price, total_value=total_value, cash=cash, balance=balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)
        if not shares:
            return apology("must provide shares", 400)
        if int(shares) <= 0:
            return apology("shares must be a positive integer", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        total_cost = stock["price"] * int(shares)
        if total_cost > cash:
            return apology("not enough cash", 400)
        else:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, datetime('now'))", session["user_id"], stock["symbol"], shares, stock["price"])
            return redirect("/")
    else:
        return render_template("buy.html")

    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT symbol, shares, price, time FROM transactions WHERE user_id = ? ORDER BY time DESC", session["user_id"])

    symbol = []
    shares = []
    price = []
    time = []

    for transaction in transactions:
        symbol.append(transaction["symbol"])
        shares.append(transaction["shares"])
        price.append(usd(transaction["price"]))
        time.append(transaction["time"])

    return render_template("history.html", symbol=symbol, shares=shares, price=price, time=time)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", name=stock["name"], price=usd(stock["price"]), symbol=symbol)
    else:
        return render_template("quote.html")

    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide confirmation", 400)
        elif password != confirmation:
            return apology("passwords do not match", 400)

        hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
            return redirect("/login")
        except:
            return apology("username already exists", 400)
    else:
        return render_template("register.html")

    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        available_shares = db.execute("SELECT SUM(shares) FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], stock["symbol"])[0]["SUM(shares)"]

        if not stock:
            return apology("invalid symbol", 400)

        if not shares or int(shares) <= 0:
            return apology("must provide a positive number of shares", 400)
        elif int(shares) > available_shares:
            return apology("not enough shares to sell", 400)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES (?, ?, ?, ?, datetime('now'))", session["user_id"], stock["symbol"], -int(shares), stock["price"])
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", stock["price"] * int(shares), session["user_id"])

        return redirect("/")

    else:
        return render_template("sell.html")

    return apology("TODO")
