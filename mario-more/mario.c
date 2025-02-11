#include <cs50.h>
#include <stdio.h>

void print_row(int spaces, int lbricks, int rbricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print a pyramid of that height
    for (int i = 0; i < n; i++)
    {
        // Print row of bricks
        print_row(n - (i + 1), i + 1, i + 1);
    }
}
void print_row(int spaces, int lbricks, int rbricks)
{
    // Print spaces
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    // Print row of left bricks
    for (int i = 0; i < lbricks; i++)
    {
        printf("#");
    }
    // Print gap
    for (int i = 0; i < 2; i++)
    {
        printf(" ");
    }
    // Print row of right bricks
    for (int i = 0; i < lbricks; i++)
    {
        printf("#");
    }
    // Print \n
    printf("\n");
}
