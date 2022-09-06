// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include <string.h>

#include <strings.h>

#include <stdlib.h>

#include <stdio.h>

#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 4000;

// Number of words in dictionary
int TOTAL_WORDS;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int key = hash(word);

    // Search linked list
    node *p;
    for (p = table[key]; p; p = p->next)
    {
        if (strcasecmp(p->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long sum = 5381;
    for (int i = 0; word[i]; i++)
    {
        //if (word[i] >= 'a' && word[i] <= 'z')
        //{
            //sum += word[i] - 'a';
        sum = sum * 33 + tolower(word[i]);

        //}
        /*else if (word[i] >= 'A' && word[i] <= 'Z')
        {
            sum += word[i] - 'A';
        }
        else
        {
            sum += word[i];
        }*/
    }
    return sum % N;
}

node *insert(node *head, char *word)
{
    node *p = (node *) malloc(sizeof(node));

    if (p == NULL)
    {
        return NULL;
    }

    strcpy(p->word, word);
    p->next = head;

    return p;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // Check if return value is NULL
    if (file == NULL)
    {
        return false;
    }

    //Read strings from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // printf("---%s---\n", word);
        int key = hash(word);

        // Insert word in hash set at right index
        table[key] = insert(table[key], word);

        if (table[key] == NULL)
        {
            return false;
        }

        // Keep count of words in dict
        TOTAL_WORDS++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return TOTAL_WORDS;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through hash table and through llists
    for (int i = 0; i < N; i++)
    {
        // how do i link it to table[i];
        for (node *p = table[i]; p;)
        {
            node *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    return true;
}
