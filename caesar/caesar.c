#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // One command-line argument
    if (argc > 2 || argc < 2)
    {
        printf("Usage: ./caeser key\n");
        return 1;
    }
    else
    {
        int flag = 0;
        for (int i = 0, lenght = strlen(argv[1]); i < lenght; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                flag += 1;
            }
        }
        if (flag != 0)
        {
            printf("Usage: ./caeser key\n");
            return 1;
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int key = atoi(argv[1]);

    // Prompt user for plaintext
    string text = get_string("plaintext:  ");

    // For each character in the plaintext:
    printf("ciphertext: ");
    for (int i = 0, lenght = strlen(text); i < lenght; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                char c = text[i] - 65;
                c = (c + key) % 26;
                c += 65;
                printf("%c", c);
            }
            else if (islower(text[i]))
            {
                char c = text[i] - 97;
                c = (c + key) % 26;
                c += 97;
                printf("%c", c);
            }
        }
        else
        {
            char c = text[i];
            printf("%c", c);
        }
    }
    printf("\n");
}
