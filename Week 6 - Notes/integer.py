# Doesn't handle exception

# Prompt user for an integer
n = int(input("Input: "))
print("Integer")


# Handles exception
# Prompt user for an integer
try:
    n = int(input("Input: "))
    print("Integer.")
except ValueError:
    print("Not integer.")
