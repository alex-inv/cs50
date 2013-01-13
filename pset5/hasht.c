/*************************************************************************
 * hasht.c
 *
 * Implements a hash-table structure.
 ************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "hasht.h"

/**
* djb2 hash function - calculates hash for lowercase
*/
unsigned long hash(const char *str)
{
    unsigned long hash_val = 5381;
    int c;
    
    while ((c = *str++))
    {
        hash_val = ((hash_val << 5) + hash_val) + tolower(c);
    }
    
    return hash_val;
}

/**
* Initializes a hash-table with a given size
*/
bool hasht_init(hash_table *tbl, unsigned int size)
{
    // Allocate an array of given size for nodes
    tbl->values = (node **)calloc(size, sizeof(node *));
    
    if (tbl->values == NULL)
        return false;
    
    // Set the sizes correctly
    tbl->table_size = size;
    tbl->dict_size = 0;
    
    return true;
}
 
/**
* Frees a hash-table
*/
bool hasht_free(hash_table *tbl)
{
    for (int i = 0; i < tbl->table_size; i++)
        node_free(tbl->values[i]);
        
    free(tbl->values);
    
    return true;
}
 
/**
* Appends a string to a hash-table
*/
bool hasht_append(hash_table *tbl, char *str)
{
    // Calculate the correct hash
    unsigned int hash_value = hash(str) % tbl->table_size;
    
    // Append the string
    node_add(&(tbl->values[hash_value]), str);
    
    tbl->dict_size++;
    
    return true;
}
 
/**
* Checks if a string is in a hash-table
*/
bool hasht_lookup(hash_table *tbl, const char *str)
{   
    // Calculate the correct hash
    unsigned int hash_value = hash(str) % tbl->table_size;
    
    // Find the string
    return node_lookup(tbl->values[hash_value], str);
}

/**
* Writes contents of a hash-table into a file with printing some statistics.
*/
void hasht_print(hash_table *tbl)
{
    FILE *fw = fopen("hash_table.txt", "w");
    
    int elem_count = 0;
    int bucket_count = 0;

    for (int i = 0; i < tbl->table_size; i++)
    {
        int count = node_print(fw, i, tbl->values[i]);
        
        elem_count += count;
        bucket_count += count ? 1 : 0;
    }
    
    fprintf(fw, "\nStatistics:\n");
    fprintf(fw, "Table has %d buckets\n", tbl->table_size);
    fprintf(fw, "Table has %d elements\n", elem_count);
    fprintf(fw, "Load factor is %.2f\n", (float)elem_count / tbl->table_size);
    fprintf(fw, "Table has %d filled buckets\n", bucket_count);
    fprintf(fw, "%% bucket used is %.2f\n", (float)bucket_count / tbl->table_size * 100);
    
    fclose(fw);
}
