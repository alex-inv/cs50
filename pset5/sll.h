/*************************************************************************
 * sll.h
 *
 * Declares a simple singly-linked list structure.
 ************************************************************************/
 
#ifndef SLL_H
#define SLL_H

typedef struct node
{
    // The string to store in the node
    char *value;

    // The link to the next node in the list
    struct node* next;
}
node;

/**
 * Returns true if a node in the list contains the value i and false
 * otherwise.
 */
bool node_lookup(node *list, const char *val);

/**
 * Puts a new node containing i at the front (head) of the list.
 */
void node_add(node **list, char *val);

/**
 * Frees the space allocated by a single linked list
 */
void node_free(node *list);

/**
 * Debug - prints the contents of a node to a file. File must be opened.
 * Returns a number of elements in the list
 */
int node_print(FILE *f, unsigned int idx, node *list);

#endif
