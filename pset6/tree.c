/****************************************************************************
 * tree.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a tree for Huffman coding.
 ***************************************************************************/

#include <stdlib.h>

#include "tree.h"

/**
 * Makes a tree with no children, returning pointer thereto
 * or NULL on error.
 */
Tree* mktree(void)
{
    // allocate tree
    Tree* tree = malloc(sizeof(Tree));
    if (tree == NULL)
    {
        return NULL;
    }

    // initialize tree
    tree->symbol = 0x00;
    tree->frequency = 0;
    tree->left = NULL;
    tree->right = NULL;

    // return tree
    return tree;
}

/**
 * Deletes a tree and all its descendants, if any.
 */
void rmtree(Tree* t)
{
    // ensure tree is not NULL
    if (t == NULL)
    {
        return;
    }

    // remove left subtree, if any
    if (t->left != NULL)
    {
        rmtree(t->left);
    }

    // remove right subtree, if any
    if (t->right != NULL)
    {
        rmtree(t->right);
    }

    // free root
    free(t);
}
