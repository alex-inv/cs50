/****************************************************************************
 * dump.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Dumps contents of a huff-compressed file in human-readable form.
 ***************************************************************************/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

// first and last symbols to dump
#define FIRST '!'
#define LAST '~'

// number of columns to use
#define COLS 8

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: %s input\n", argv[0]);
        return 1;
    }

    // open input
    Huffile* input = hfopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s for reading.\n", argv[1]);
        return 1;
    }

    // read in header
    Huffeader header;
    if (hread(&header, input) == false)
    {
        hfclose(input);
        printf("Could not read header.\n");
        return 1;
    }

    // check for magic number
    if (header.magic != MAGIC)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }

    // check checksum
    int checksum = header.checksum;
    for (int i = 0; i < SYMBOLS; i++)
    {
        checksum -= header.frequencies[i];
    }
    if (checksum != 0)
    {
        hfclose(input);
        printf("File was not huffed.\n");
        return 1;
    }

    // determine number of rows to use
    const int rows = (int) ceil((LAST - FIRST) / (double) COLS);

    // dump frequencies in a nice table
    printf("\n");
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            int index = FIRST + row + rows * col;
            if (index > LAST)
            {
                break;
            }
            printf("%c %-6d  ", index, header.frequencies[index]);
        }
        printf("\n");
    }
    printf("\n");

    // dump bits contiguously
    int bit;
    while ((bit = bread(input)) != EOF)
    {
        printf("%d", bit);
    }
    printf("\n\n");

    // close input
    hfclose(input);

    // that's all folks!
    return 0;
}
