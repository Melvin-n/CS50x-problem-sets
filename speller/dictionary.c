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
    while (table[hashval] != NULL)
    {
        if (strcasecmp(table[hashval]->word, word) == 0)
        {
            return true;
        }
        else
        {
            table[hashval] = table[hashval]->next;

        }
    }

    return false;

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
    char* currentword[LENGTH + 1];
    FILE *dict = fopen(dictionary, "r");
    //check for error in reading file
    if (dict == NULL)
    {
        return false;
    }
    else
    {
        //declare list of size dictionary to read dict into array list
        //char *list [sizeof(dict)];
        //read each word in file into list until returns value is EOF

        while (fscanf(dict, "%c", *currentword) != EOF)
        {
            //create memory for a node
            node *head = NULL;
            node *n = malloc(sizeof(node));
            if (n == NULL)
            {
                return false;
            }

            else
            {
                //copy word from list into hash table
                strcpy(n->word, *currentword);
                //get hash value
                int hashval = hash(*currentword);
                //set next val of new node to prev first node
                n->next = head;
                //set next val of head to new node
                head = n;
                counter ++;
            }
        }
    }
    fclose(dict);
    return 0;
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
    // TODO
    return false;
}
