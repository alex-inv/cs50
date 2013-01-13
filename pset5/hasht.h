/*************************************************************************
 * hasht.h
 *
 * Declares a hash-table structure.
 ************************************************************************/
 
#ifndef HASHT_H
#define HASHT_H

#include "shared.h"
#include "sll.h"

typedef struct
{
   // An array of singly-linked lists
   node *values[HASH_TABLE_SIZE];
    
   // The size of a dictionary
   unsigned int dict_size;
}
hash_table;
 
/**
* Initializes a hash-table with a given size
*/
bool hasht_init(hash_table *tbl);
 
/**
* Frees a hash-table
*/
bool hasht_free(hash_table *tbl);
 
/**
* Appends a string to a hash-table
*/
bool hasht_append(hash_table *tbl, char *str);
 
/**
* Checks if a string is in a hash-table
*/
bool hasht_lookup(hash_table *tbl, const char *str);

/**
* Writes contents of a hash-table into a file with printing some statistics.
*/
void hasht_print(hash_table *tbl);
 
#endif
