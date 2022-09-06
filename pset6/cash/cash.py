from cs50 import get_float

# Prompt user for an amount of change in $
while True:
    dollars = get_float("Change owed: ")
    if dollars >= 0:
        break

# Convert input from $ to cents
cents = round(dollars * 100)
# print(cents)

# Use the largest coins possible, keeping track of coins used
t = x = y = z = 0
n = cents

# Check if big enough for 25c
while True:
    if n < 25:
        break
    n = n - 25
    t += 1
# print(t)

# Check if big enough for 10c
while True:
    if n < 10:
        break
    n = n - 10
    x += 1
# print(x)

# Check if big enough for 5c
while True:
    if n < 5:
        break
    n = n - 5
    y += 1
# print(y)
# Check if big enough for 1c
while True:
    if n < 1:
        break
    n = n - 1
    z += 1
# print(z)

# Add up and print no. of coins
print(t + x + y + z)


