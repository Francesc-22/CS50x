amex = ["34", "37"]
mastercard = ["51", "52", "53", "54", "55"]
visa = ["4"]

lenghts = [13, 15, 16]

def check(n):
    if len(n) not in lenghts:
        return False

    other = False
    result = 0
    n = int(n)

    while n > 0:
        x = n % 10

        if other:
            x = x * 2
            if (x > 9):
                result += (x % 10) + (x // 10)
            else:
                result += x
        else:
            result += x
        other = not other
        n //= 10

    if (result % 10 == 0):
        return True

    return False



number = (input("Number: "))
card = check(number)

if not card:
    print("INVALID\n")
    exit()
else:
    if number[0:2] in amex:
        print("AMEX\n")
    if number[0:2] in mastercard:
        print("MASTERCARD\n")
    if number[0:1] in visa:
        print("VISA\n")
