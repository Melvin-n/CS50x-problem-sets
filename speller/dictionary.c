// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

int counter = 0;
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//changed 1 to 60
const unsigned int N = 60;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
//check if the word from the txt is in the dictionary
bool check(const char *word)
{
    // TODO
    int hashval = hash(word);
    node *cursor = table[hashval];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;

            if (cursor == NULL)
            {
                return false;
            }

        }
    }
    return 0;


}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //source: Dan Bernstein, djb2 http://www.cse.yorku.ca/~oz/hash.html
    // TODO
    unsigned long hash = 5381;

    int c = *word;

    c = tolower(c);

    while (*word != 0)
    {

        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);

    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
//load dictionary into hash table, hash table is an array of linked lists
bool load(const char *dictionary)
{
    // TODO
    //OPEN DICTIONARY FILE
    char currentword[LENGTH + 1];
    FILE *dict = fopen(dictionary, "r");
    //check for error in reading file
    if (dict == NULL)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //declare list of size dictionary to read dict into array list
    //char *list [sizeof(dict)];
    //read each word in file into list until returns value is EOF
    while (fscanf(dict, "%s\n", currentword) != EOF)
    {
        //create memory for a node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }


        //copy word from list into hash table
        strcpy(n->word, currentword);
        //get hash value
        int hashval = hash(currentword);
        //set next val of new node to prev first node
        if (table[hashval] == NULL)
        {
            //if bucket is empty, set the head of the bucket to the node
            n->next = NULL;
            table[hashval] = n;
            counter++;
        }
        else
        {
            //if not empty, link the current node to the head, then head becomes current node
            n->next = table[hashval];
            table[hashval] = n;
            counter ++;
        }

    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            
        }
    }
    return true;
}
