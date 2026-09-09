import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if name and month and day:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", rows=rows)


@app.route("/delete", methods=["POST"])
def delete():
    # Get the id of the entry to delete
    id = request.form.get("id")

    # Delete the entry from the database
    db.execute("DELETE FROM birthdays WHERE id = ?", id)

    return redirect("/")


@app.route("/update", methods=["POST"])
def update():
    # Get the id of the entry to update
    id = request.form.get("id")

    # Get the new values for name, month, and day
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    if name and month and day:
        # Update the entry in the database
        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?", name, month, day, id)

    return redirect("/")
