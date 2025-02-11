#include <cs50.h>
#include <math.h>
#include <stdio.h>

// AMEX - 15 digits, starts with 34 or 37
// MASTERCARD - 16 digits, starts with 51,52,53,54, or 55
// VISA - 13 or 16 digits, starts with 4

long get_starting_digits(long number);
long get_first_digit(long number);

int main(void)
{
    // Prompt the user for a credit card number
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);
    // Calculate checksum
    long original = number;
    int last;
    int sum = 0;
    int counter = 1;
    while (number >= 1)
    {
        last = number % 10;
        if (counter % 2 == 0)
        {
            last *= 2;
            if (last >= 10)
            {
                int fdigit = last / 10;
                int ldigit = last % 10;
                sum += fdigit;
                sum += ldigit;
            }
            else
            {
                sum += last;
            }
        }
        else
        {
            sum += last;
        }
        number = number / 10;
        counter++;
    }
    if (sum % 10 == 0)
    {
        // Check for card length
        int numDigits = floor(log10(original)) + 1;
        int start = get_starting_digits(original);
        int firstDigit = get_first_digit(original);
        if (numDigits == 15)
        {
            // Check starting digits for AMEX
            if (start == 34 || start == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (numDigits == 16)
        {
            // Check starting digits for MASTERCARD
            if (start == 51 || start == 52 || start == 53 || start == 54 || start == 55)
            {
                printf("MASTERCARD\n");
            }
            // Check starting digits for VISA
            else if (firstDigit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (numDigits == 13)
        {
            // Check starting digits for VISA
            if (firstDigit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_starting_digits(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    return number;
}

long get_first_digit(long number)
{
    while (number >= 10)
    {
        number /= 10;
    }
    return number;
}
