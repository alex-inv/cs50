/****************************************************************************
 * tree.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Defines a tree for Huffman coding.
 ***************************************************************************/

#ifndef TREE_H
#define TREE_H

/**
 * Defines a Huffman tree (or, more generally, a node thereof).
 */
typedef struct tree
{
    char symbol;
    int frequency;
    struct tree* left;
    struct tree* right;
}
Tree;

/**
 * Makes a tree with no children, returning pointer thereto
 * or NULL on error.
 */
Tree* mktree(void);

/**
 * Deletes a tree and all its descedants, if any.
 */
void rmtree(Tree* t);

#endif

