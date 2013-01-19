/****************************************************************************
 * forest.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a forest for Huffman trees.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>

#include "forest.h"
#include "tree.h"

/**
 * Makes a forest, initially barren, returning pointer thereto
 * or NULL on error.
 */
Forest* mkforest(void)
{
    // allocate space for forest
    Forest *f = malloc(sizeof(Forest));
    if (f == NULL)
    {
        return NULL;
    }

    // initialize forest as barren
    f->first = NULL;

    // return forest
    return f;
}

/**
 * Removes a tree with lowest weight from the forest, returning
 * pointer thereto or NULL if forest is barren.
 */
Tree* pick(Forest* f)
{
    // ensure source is not NULL
    if (f == NULL)
    {
        return NULL;
    }

    // check whether forest is barren
    if (f->first == NULL)
    {
        return NULL;
    }

    // pick tree with lowest weight
    Tree* tree = f->first->tree;

    // clear tree's plot
    Plot* plot = f->first;
    f->first = f->first->next;
    free(plot);

    // return tree
    return tree;
}


/**
 * Plants a tree in the forest, provided that tree's frequency is non-0.
 * Returns true on success and false on error.
 */
bool plant(Forest* f, Tree* t)
{
    // ensure destination and source are not NULL
    if (f == NULL || t == NULL)
    {
        return false;
    }

    // reject useless trees
    if (t->frequency == 0)
    {
        return false;
    }

    // prepare tree for forest
    Plot* plot = malloc(sizeof(Plot));
    if (plot == NULL)
    {
        return false;
    }
    plot->tree = t;

    // find tree's position in forest
    Plot* trailer = NULL;
    Plot* leader = f->first;
    while (leader != NULL)
    {
        // keep trees sorted first by frequency then by symbol
        if (t->frequency < leader->tree->frequency)
        {
            break;
        }
        else if (t->frequency == leader->tree->frequency
            && t->symbol < leader->tree->symbol)
        {
            break;
        }
        else
        {
            trailer = leader;
            leader = leader->next;
        }
    }

    // either insert plot at start of forest
    if (trailer == NULL)
    {
        plot->next = f->first;
        f->first = plot;
    }

    // or insert plot in middle or at end of forest
    else
    {
        plot->next = trailer->next;
        trailer->next = plot;
    }

    // success!
    return true;
}

/**
 * Deletes a forest (and all of its trees).
 * Returns true on success and false on error.
 */

bool rmforest(Forest* f)
{
    // ensure source is not NULL
    if (f == NULL)
    {
        return false;
    }

    // clear forest's trees
    while (f->first != NULL)
    {
        Plot* plot = f->first;
        f->first = f->first->next;
        rmtree(plot->tree);
        free(plot);
    }

    // free forest
    free(f);

    // success!
    return true;
}
