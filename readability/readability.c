#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float L = (letters / words) * 100.0;
    float S = (sentences / words) * 100.0;
    float index = round(0.0588 * L - 0.296 * S - 15.8);
    int grade = (int) index;

    // Print the grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }
}

int count_letters(string text)
{
    // Return the number of letters
    float letters = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    return letters;
}

int count_words(string text)
{
    // Return the number of words
    float spaces = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == ' ')
        {
            spaces += 1;
        }
    }
    return spaces + 1;
}

int count_sentences(string text)
{
    // Return the number of sentences
    float punctuation = 0;
    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (text[i] == '.')
        {
            punctuation += 1;
        }
        else if (text[i] == '!')
        {
            punctuation += 1;
        }
        else if (text[i] == '?')
        {
            punctuation += 1;
        }
    }
    return punctuation;
}
