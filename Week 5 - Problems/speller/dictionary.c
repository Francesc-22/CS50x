// Implements a dictionary's functionality

#include <ctype.h>
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
const unsigned int N = 26;

// Hash table
node *table[N];

// Counts the number of words in dictionary.
unsigned int counter = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // Finding the index.
    int index = hash(word);

    // Iterate over nodes in list
    for (node *i = table[index]; i != NULL; i = i->next)
    {
        // If word is on the table.
        if (strcasecmp(i->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(toupper(word[0])) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open file.\n");
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(dic, "%s", buffer) != EOF)
    {
        // Create a new node.
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(dic);
            return false;
        }

        // Copy de word to the node.
        strcpy(n->word, buffer);
        n->next = NULL;

        // Finding the index of the hash table for the word.
        unsigned int index = hash(buffer);

        // Inserting the node to the beggining of the hash table.
        n->next = table[index];

        // Update the index to be our node.
        table[index] = n;

        // Update counter.
        counter++;
    }

    fclose(dic);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Alternatively.
    //unsigned int counter = 0;
    //for (int index = 0; index < N; index++)
    //{
    //    node *cursor = table[index];
    //    while (cursor != NULL)
    //    {
    //        counter++;
    //        cursor = cursor->next;
    //    }
    //}
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int index = 0; index < N; index++)
    {
        node *cursor = table[index];
        while (cursor != NULL)
        {
            node *next = cursor->next;
            free(cursor);
            cursor = next;
        }
    }
    return true;
}
