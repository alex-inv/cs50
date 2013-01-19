/****************************************************************************
 * forest.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Defines a forest for Huffman trees.
 ***************************************************************************/

#ifndef FOREST_H
#define FOREST_H

#include "tree.h"

/**
 * Space for a tree in a forest.
 */
typedef struct plot
{
    Tree* tree;
    struct plot* next;
}
Plot;

/**
 * A forest for Huffman trees, implemented as a singly linked list.
 */
typedef struct forest
{
    Plot* first;
}
Forest;

/**
 * Makes a forest, initially barren, returning pointer thereto
 * or NULL on error.
 */
Forest* mkforest(void);

/**
 * Removes a tree with lowest weight from the forest, returning
 * pointer thereto or NULL if forest is barren.
 */
Tree* pick(Forest* f);

/**
 * Plants a tree in the forest, provided that tree's frequency is non-0.
 * Returns true on success and false on error.
 */
bool plant(Forest* f, Tree* t);

/**
 * Deletes a forest (and all of its trees).
 * Returns true on success and false on error.
 */
bool rmforest(Forest* f);

#endif
