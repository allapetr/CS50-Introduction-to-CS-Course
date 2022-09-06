from cs50 import get_int

# Prompt user for height
n = 0
while n < 1 or n > 8:
    n = get_int("Height: ")

# Build piramid
for x in range(n):
    for z in range(n - (x + 1)):
        print(" ", end="")
    for y in range(x + 1):
        print("#", end="")
    print()
