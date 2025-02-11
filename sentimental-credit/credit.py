from cs50 import get_int
import sys

while True:
    number = get_int('Number: ')
    nstr = str(number)
    if number > 0 and 13 <= len(nstr) <= 16:
        break
    else:
        print('INVALID')
        sys.exit()

'''Checksum'''
sum = 0

for i in range(len(nstr) - 2, -1, -2):
    mult = int(nstr[i]) * 2
    if mult >= 10:
        left = mult // 10
        right = mult % 10
        sum += left + right
    else:
        sum += mult

for i in range(len(nstr) - 1, -1, -2):
    sum += int(nstr[i])

if sum % 10 == 0:
    if len(nstr) == 15:
        if nstr[0:2] == '34' or nstr[0:2] == '37':
            print('AMEX')
        else:
            print('INVALID')
    elif len(nstr) == 16:
        if nstr[0:2] == '51' or nstr[0:2] == '52' or nstr[0:2] == '53' or nstr[0:2] == '54' or nstr[0:2] == '55':
            print('MASTERCARD')
        elif nstr[0] == '4':
            print('VISA')
        else:
            print('INVALID')
    elif len(nstr) == 13:
        if nstr[0] == '4':
            print('VISA')
        else:
            print('INVALID')
    else:
        print('INVALID')
else:
    print('INVALID')
