#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is yout name? ");
    printf("hello, %s\n", name);
}
