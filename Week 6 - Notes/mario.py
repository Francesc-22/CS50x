from cs50 import get_int

# Prints a column of n bricks with a loop
while True:
    n = get_int("Height: ")
    if n > 0:
        break

for i in range(n):
    print("#")


# Prints a row of 4 question marks with a loop
for i in range(4):
    print("?", end="")
print()

# Prints a row of 4 question marks without a loop
print("?" * 4)


# Prints a 3-by-3 grid of bricks with loops
for i in range(3):
    for j in range(3):
        print("#", end="")
    print()
