// Implements a dictionary's functionality
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table, set to 120,000
const unsigned int N = 120000;

// Hash table
node *table[N];

// Declare bool for whether the dictionary successfully loads
bool canitload = false; //initialise to false

//initialise int pointer for n(words) in dictionary
int dicsize = 0;

// Loads dictionary into memory, returning true if successful else false //TODO
bool load(const char *dictionary)
{
    int *tmp = &dicsize; //create temporary pointer to dicsize

    FILE *dicfile = fopen(dictionary, "r");
    if (dicfile == NULL)
    {
        printf("Could not open dictionary file.\n");
        return false;
    }

    if (feof(dicfile))
    {
        printf("File starts with EOF");
        return false;
    }

    while (!feof(dicfile)) //iterates over words in dictionary until EOF
    {
        char *word2hash = malloc((LENGTH + 1) * sizeof(char)); //allocates memory
        memset(word2hash, 0, strlen(word2hash)); //zeroes word2hash for each iteration

        int c; //initialise c
        for (int i = 0; true; i++) //iterates over dictionary until \n reached
        {
            c = fgetc(dicfile);

            if (c == 10) //break if c == \n
            {
                break;
            }

            word2hash[i] = c; //updates elements of word2hash to = chars in dictionary words

            if (feof(dicfile)) //break if EOF
            {
                break;
            }
        }

        unsigned int h = hash(word2hash); //obtain hash for current word2hash

        //place word2hash in appropriate bucket

        node *n = malloc(sizeof(node)); //allocate memory for new node
        if (n == NULL)
        {
            printf("Error: could not allocate memory to insert node");
            return false;
        }

        strcpy(word2hash, n -> word); //copy word2hash into new node
        n -> next = table[h]; //point new node to existing node that table[h] is pointing to //NULL if bucket empty

        *tmp += 1; //increase dicsize //hehehehehehehehe

        table[h] = n; //point table[h] towards new node
        free(word2hash); //frees memory
    }

    return true;
    canitload = true; //updates global variable canitload to true
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 5831; //initialise hash to 5831

    for (int i = 0, len = strlen(word); i < len; i++) //iterate over letters in word
    {
        hash = hash * 33 + tolower(word[i]); //update hash //use tolower to ensure hash is case insensitive
    }

    hash = hash % N; //limit to N buckets
    return hash;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dicsize - 1; //minus 1 to account for empty lastline
}

// Returns true if word is in dictionary else false
bool check(const char *word) //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG //DEBUG
{
    unsigned int h = hash(word); //obtain hash for string input
    node *ptr = NULL; //initialise temporary pointer to NULL

    if (table[h] == NULL)
    {
        return false; //return false if corresponding bucket empty
    }

    else
    {
        ptr = table[h]; //set ptr to first node in linked list indexed in h
        while (ptr != NULL) //iterate over nodes in linked list
        {
            if (strcasecmp(word, ptr -> word))
            {
                return true; //return true if string input equals string in table[h].word
            }

            else
            {
                ptr = ptr -> next; //point ptr at next node in linked list
            }
        }

        return false; //return false if matching string not found
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //iterate over N buckets in hashtable
    {
        node *ptr = NULL; //initialise temporary pointer to NULL

        if (table[i] == NULL)
        {
            break; //break for loop if bucket empty
        }

        else //free memory from start of linked list
        {
            ptr = table[i]; //point ptr to first node in linked list
            table[i] = ptr -> next; //point hashtable to next node in linked list
            free(ptr);
        }
    }

    //check if all buckets empty
    for (int i = 0; i < N; i++) //iterate over N buckets in hashtable
    {
        if (table[i] == NULL)
        {
            break; //break for loop if bucket empty
        }

        else
        {
            printf("Error: dictionary cannot be unloaded");
            return false;
        }

    }

    return true;
}
