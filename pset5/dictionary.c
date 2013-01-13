/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "dictionary.h"

//#define DEBUG

// Hash-table for storing the dictionary
hash_table dict;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return hasht_lookup(&dict, word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Open the file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
        return false;
    
    // Initialize the hash table
    hasht_init(&dict);
    
    // Load words from dictionary
    char buffer[LENGTH + 2];
    while (fgets(buffer, LENGTH + 2, f))
    {
        // Overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';
        
        // Append the word to the hash table
        hasht_append(&dict, buffer);
    }
    
    // Debug - print the contents of a hash-table
    #ifdef DEBUG
    hasht_print(&dict);
    #endif
        
    fclose(f);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dict.dict_size;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return hasht_free(&dict);
}
