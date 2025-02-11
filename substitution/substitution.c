#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool checkLetters(string s);

int main(int argc, string argv[])
{
    // One command-line argument with 26 alphabetic characters
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int lenght = strlen(argv[1]);
        if (lenght != 26)
        {
            printf("Key must containing 26 characters\n");
            return 1;
        }
        else
        {
            if (!checkLetters(argv[1]))
            {
                return 1;
            }
        }
    }

    // Input the plaintext
    string text = get_string("plaintext:  ");

    // Output the ciphertext
    printf("ciphertext: ");
    for (int i = 0, l_text = strlen(text); i < l_text; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                char c = toupper(argv[1][text[i] - 'A']);
                printf("%c", c);
            }
            else if (islower(text[i]))
            {
                char c = tolower(argv[1][text[i] - 'a']);
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

bool checkLetters(string s)
{
    int lenght = strlen(s);
    int flag = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (!isalpha(s[i]))
        {
            flag += 1;
        }
        else
        {
            for (int c = i + 1; c < lenght; c++)
            {
                if (tolower(s[i]) == tolower(s[c]))
                {
                    printf("Key must containing each letter exactly once\n");
                    return false;
                }
            }
        }
    }
    if (flag != 0)
    {
        printf("All character must be alphabetic\n");
        return false;
    }
    return true;
}
