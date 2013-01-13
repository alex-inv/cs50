/*************************************************************************
 * sll.c
 *
 * Implements a simple singly-linked list structure.
 ************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <strings.h>

#include "sll.h"

/**
 * Creates a new node.
 */
node *new_node(char *val)
{
    node *result = (node *)malloc(sizeof(node));
    
    result->value = (char *)malloc((strlen(val) + 1) * sizeof(char));
    strncpy(result->value, val, strlen(val) + 1);
    result->next = NULL;
    
    return result;
}

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool node_lookup(node *list, const char *val)
{
    node *t = list;
    
    while (t != NULL)
    {
        if (!(strcasecmp(val, t->value)))   // Case-insensitive comparing
            return true;
    
        t = t->next;
    }
    
    return false;
}

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void node_add(node **list, char *val)
{
    node *new = new_node(val);
    
    new->next = *list;
    *list = new;
}

/**
 * Frees the space allocated by a single linked list.
 */
void node_free(node *list)
{
    node *t = list;
    
    while (t != NULL)
    {
        node* next = t->next;
        
        free(t->value);
        free(t);
        
        t = next;
    }
}

/**
 * Debug - prints the contents of a node to a file. File must be opened.
 * Returns a number of elements in the list
 */
int node_print(FILE *f, unsigned int idx, node *list)
{
    int count = 0;
    node *t = list;
    
    if (t != NULL)
    {
        fprintf(f, "%d:\t", idx);
        
        while (t != NULL)
        {
            fprintf(f, "%s\t", t->value);
            t = t->next;
            count++;
        }
        
        fprintf(f, "\n");
    }
    
    return count;
}
