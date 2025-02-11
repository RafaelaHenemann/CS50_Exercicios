from cs50 import get_float

while True:
    n = get_float('Change: ')
    if n > 0:
        break

n = round(n * 100)

quarters = n // 25
n = n - quarters * 25
dimes = n // 10
n = n - dimes * 10
nickels = n // 5
n = n - nickels * 5
pennies = n

coins = int(quarters + dimes + nickels + pennies)

print(coins)
