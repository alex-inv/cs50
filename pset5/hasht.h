/*************************************************************************
 * hasht.h
 *
 * Declares a hash-table structure.
 ************************************************************************/
 
#ifndef HASHT_H
#define HASHT_H
 
#include "sll.h"

//#define HASH_TABLE_SIZE 143093
//#define HASH_TABLE_SIZE 76801
#define HASH_TABLE_SIZE 286199
 
typedef struct
{
   // An array of singly-linked lists
   node **values;
    
   // The size of a table
   unsigned int table_size;
    
   // The size of a dictionary
   unsigned int dict_size;
}
hash_table;
 
/**
* Initializes a hash-table with a given size
*/
bool hasht_init(hash_table *tbl, unsigned int size);
 
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
