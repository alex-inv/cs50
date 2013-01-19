/****************************************************************************
 * puff.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Decompresses a Huffmann-encoded file.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "forest.h"
#include "huffile.h"
#include "tree.h"

typedef struct hf_buffer
{
	int idx;
	int bits[32];
} Hf_buffer;

// Construct a populated Huffmann tree from a Huffmann header
Tree *ht_parse(Huffeader *header)
{
	// A forest for storing elements in sorted order
	Forest *forest = mkforest();
	
	// Now go and read those frequences
	for (int i = 0; i < SYMBOLS; i++)
	{
		 // Only if a frequency is non-zero
		 if (header->frequencies[i])
		 {
		 	// Construct a single-node tree
		 	Tree *leaf = mktree();
		 	
		 	leaf->symbol = i;
		 	leaf->frequency = header->frequencies[i];
		 	
		 	// Add it to the forest
		 	plant(forest, leaf);
		 }
	}
	
	// Iterate the forest and construct a Huffmann tree
	Tree *left, *right, *parent, *result;
	
	while ((left = pick(forest)) != NULL)
	{
		result = left;
	
		// If this one was not the last
		if ((right = pick(forest)) != NULL)
		{
			parent = mktree();
			
			parent->frequency = left->frequency + right->frequency;
			parent->left = left;
			parent->right = right;
			
			plant(forest, parent);
		}
	}
	
	// Free the forest
	rmforest(forest);
	
	// Return the root of a Huffmann tree
	return result;
}

// Recursively traverse the Huffmann tree to find a character
bool ht_lookup(Tree *tree, int *bit_path, int length, char *c)
{
	// Bit_path is over
	if (length < 0)
		return false;
		
	// Tree is empty
	if (tree == NULL)
		return false;
	
	// If the tree is a leaf
	if (tree->right == NULL && tree->left == NULL)
	{
		*c = tree->symbol;
		return true;
	}
	
	// Analyze current bit
	int bit = *bit_path;
	
	if (bit)
		return ht_lookup(tree->right, bit_path + 1, length - 1, c);
	else
		return ht_lookup(tree->left, bit_path + 1, length - 1, c);
}

// DEBUG
void ht_print(Tree *tree, int cur_level, int dest_level)
{
	if (tree->left != NULL)
		ht_print(tree->left, cur_level + 1, dest_level);
	
	if (cur_level == dest_level)	
		printf("sym = %d (%c) fre = %d, ", tree->symbol, tree->symbol, tree->frequency);
	
	if (tree->right != NULL)
		ht_print(tree->right, cur_level + 1, dest_level);
}

int max(int a, int b)
{
	return a > b? a : b;
}

int ht_height(Tree *tree)
{
	if (tree == NULL)
		return 0;
		
	return max(ht_height(tree->left), ht_height(tree->right)) + 1;
}

void ht_level_print(Tree *tree)
{
	for (int i = 0; i < ht_height(tree); i++)
	{
		printf("level %d: ", i);
		ht_print(tree, 0, i);
		printf("\n");
	}
}
// END DEBUG

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 3)
    {
        printf("Usage: %s input output\n", argv[0]);
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

	// Construct a Huffmann tree from the header files
	Tree *tree = ht_parse(&header);
	//ht_level_print(tree);
	
	// Open the output file
	FILE *out = fopen(argv[2], "w");
	if (out == NULL)
	{
		printf("Could not open %s for output.\n", argv[2]);
        return 1;
	}
	
	// Read bits of input file and traverse a tree
	int bit;
	char c;
	
	Hf_buffer buffer;
	buffer.idx = 0;
	
	while ((bit = bread(input)) != EOF)
	{
		buffer.bits[buffer.idx++] = bit;
	
		// If we found a character in a tree
		if (ht_lookup(tree, buffer.bits, buffer.idx, &c))
		{
			fputc(c, out);
			buffer.idx = 0;
		}
	}

	// Close output
	fclose(out);

    // close input
    hfclose(input);
    
    // Free the Huffmann tree
    rmtree(tree);

    // that's all folks!
    return 0;
}
