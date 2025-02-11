// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word
    int index = hash(word);

    // Set up a cursor
    node *cursor = table[index];

    // Check if the word is in the hash table
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Hash function
    int length = strlen(word);
    int index = 0;
    if (length == 1)
    {
        index = (toupper(word[0]) - 'A') * pow(26, 0);
    }
    else if (length == 2)
    {
        index = ((toupper(word[0]) - 'A') * pow(26, 1)) + ((toupper(word[1]) - 'A') * pow(26, 0));
    }
    else if (length >= 3)
    {
        index = ((toupper(word[0]) - 'A') * pow(26, 2)) + ((toupper(word[1]) - 'A') * pow(26, 1)) +
                ((toupper(word[2]) - 'A') * pow(26, 0));
    }
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char *word = malloc((LENGTH + 1) * sizeof(char));
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read each word in the file
    while (fscanf(source, "%s", word) != EOF)
    {
        int index = hash(word);

        // Create space for a new hash table node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word into the new node
        strcpy(n->word, word);
        n->next = table[index];

        // Add each word to the hash table
        table[index] = n;
        word_count++;
    }

    // Close the dictionary file
    fclose(source);
    free(word);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return size
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i <= (N - 1); i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
