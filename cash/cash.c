#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for change owed, in cents
    int cents;
    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    // Calculate how many quarters you should give customer
    int quarters = cents / 25;

    // Subtract the value of those quarters from cents
    cents = cents - (quarters * 25);

    // Calculate how many dimes you should give customer
    int dimes = cents / 10;

    // Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10);

    // Calculate how many nickels you should give customer
    int nickels = cents / 5;

    // Subtract the value of those nickels from remaining cents
    cents = cents - (nickels * 5);

    // Calculate how many pennies you should give customer
    int pennies = cents / 1;

    // Subtract the value of those pennies from remaining cents
    cents = cents - (pennies * 1);

    // Sum the number of quarters, dimes, nickels, and pennies used
    int coins = quarters + dimes + nickels + pennies;

    // Print that sum
    printf("%i\n", coins);
}
