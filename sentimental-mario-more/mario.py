from cs50 import get_int

while True:
    height = get_int('Height: ')
    if height >= 1 and height <= 8:
        break

for c in range(height):
    print(' ' * (height - (c + 1)), end='')
    print('#' * (c + 1), end='')
    print('  ', end='')
    print('#' * (c + 1))
