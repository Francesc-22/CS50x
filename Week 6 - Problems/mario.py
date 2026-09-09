def number():
    x = input("Height: ")

    try:
        x = int(x)
    except ValueError:
        print("Not integer.")
        return number()

    if x>8 or x<1:
        print("Integer between 1 and 8.")
        return number()

    return x

def block(n):
    for i in range(n):
        print("#", end="")

    return

def space(n):
    for i in range(n):
        print(" ", end="")

    return



height = number()

for i in range(height):
    space(height-i)
    block(i+1)
    space(2)
    block(i+1)
    print("\n", end="")
