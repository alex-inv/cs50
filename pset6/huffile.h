/****************************************************************************
 * huffile.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a layer of abstraction for Huffman-coded files.
 ***************************************************************************/

#ifndef HUFFILE_H
#define HUFFILE_H

#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Number of symbols for which we might need codes.
 */
#define SYMBOLS 256

/**
 * Magic number identifying a Huffman-coded file.
 */
#define MAGIC 0x46465548

/**
 * Allowed I/O modes for Huffman-coded files.
 */
typedef enum { READ, WRITE } mode;

/**
 * In-memory representation of a Huffman-coded file.
 */
typedef struct
{
    // 8-bit buffer
    unsigned char buffer;

    // actual file on disk
    FILE* stream;

    // current location in buffer
    unsigned char ith;
    
    // number of valid bits in file's second-to-last byte
    unsigned char zth;

    // I/O mode
    mode io;

    // size of file
    off_t size;
}
Huffile;

/**
 * Header for a Huffman-coded file.
 */
typedef struct
{
    // magic number
    int magic;

    // symbols' frequencies
    int frequencies[SYMBOLS];

    // checksum for frequencies
    int checksum;
}
Huffeader;

/**
 * Returns file's next bit (as 0 or 1) or EOF upon EOF or error.
 */
int bread(Huffile* hf);

/**
 * Lazily writes b (which must be 0 or 1) to Huffile as a single bit.
 * Returns true on success and false on failure.
 */     
bool bwrite(int b, Huffile* hf);

/**
 * Closes file.
 * Returns true on success and false on failure.
 */
bool hfclose(Huffile* hf);

/**
 * Opens path as a Huffile, returning pointer thereto or NULL on error.
 * Mode must be "r" or "w".
 */
Huffile* hfopen(const char* path, const char* mode);

/**
 * Reads in header if still at start of file.
 * Returns true on success and false on failure (e.g., not at start of file).
 */
bool hread(Huffeader* h, Huffile* hf);

/**
 * Writes out header if still at start of file.
 * Returns true on success and false on failure (e.g., not at start of file).
 */
bool hwrite(Huffeader* h, Huffile* hf);

#endif
