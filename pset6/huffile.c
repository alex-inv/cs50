/****************************************************************************
 * Huffile.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a layer of abstraction for Huffman-coded files
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "huffile.h"

/**
 * Returns file's next bit (as 0 or 1) or EOF upon EOF or error.
 */
int bread(Huffile* hf)
{
    // ensure source isn't NULL
    if (hf == NULL)
    {
        return EOF;
    }

    // check for file's end
    if (ftell(hf->stream) == hf->size - 1)
    {
        if (hf->ith == hf->zth)
        {
            return EOF;
        }
    }

    // read another buffer's worth of bits if necessary
    if (hf->ith == 0)
    {
        if (fread(&hf->buffer, sizeof(hf->buffer), 1, hf->stream) != 1)
        {
            return EOF;
        }
    }

    // prepare mask
    unsigned char mask = 1 << (7 - hf->ith);

    // advance to next bit
    hf->ith = (hf->ith + 1) % 8;

    // grab i'th bit
    return (hf->buffer & mask) ? 1 : 0;
}

/**
 * Lazily writes b (which must be 0 or 1) to Huffile as a single bit.
 *  
 * Returns true on success and false on failure.
 */
bool bwrite(int b, Huffile* hf)
{       
    // ensure destination isn't NULL
    if (hf == NULL)
    {
        return false;
    }   

    // check mode
    if (hf->io != WRITE)
    {
        return false; 
    }

    // ensure bit is valid
    if (b != 0 && b != 1)
    {
        return false;
    }

    // prepare mask
    unsigned mask = 1 << (7 - hf->ith);

    // set i'th bit in buffer if 1
    if (b == true)
    {
        // set i'th bit in buffer
        hf->buffer |= mask;
    }

    // clear i'th bit in buffer if 0
    else
    {
        // clear i'th bit in buffer
        hf->buffer &= ~mask;
    }

    // advance to next bit
    hf->ith = hf->ith + 1;

    // write buffer to disk if full
    if (hf->ith == 8)
    {
        if (fwrite(&hf->buffer, sizeof(hf->buffer), 1, hf->stream) == 1)
        {
            hf->buffer = 0x00;
            hf->ith = 0;
        }
        else
        {
            return false;
        }
    }

    // success!
    return true;
}

/**
 * Closes file.
 *
 * Returns true on success and false on failure.
 */
bool hfclose(Huffile* hf)
{
    // ensure pointer isn't NULL
    if (hf == NULL)
    {
        return false;
    }

    // ensure there's something to close
    if (hf->stream == NULL)
    {
        return false;
    }

    // be sure final buffer and its index get written out if writing
    if (hf->io == WRITE)
    {
        // write out final buffer if necessary
        if (hf->ith > 0)
        {
            if (fwrite(&hf->buffer, sizeof(hf->buffer), 1, hf->stream) != 1)
            {
                return false;
            }
        }

        // write out final buffer's index
        if (fwrite(&hf->ith, sizeof(hf->ith), 1, hf->stream) != 1)
            return false;
    }

    // close file
    if (fclose(hf->stream) != 0)
    {
        return false;
    }

    // free memory
    free(hf);

    // that's all folks
    return true;
}

/**
 * Opens path as a Huffile, returning pointer thereto or NULL on error.
 *
 * Mode must be "r" or "w".
 */
Huffile* hfopen(const char* path, const char* mode)
{
    // ensure pointers aren't NULL
    if (path == NULL || mode == NULL)
    {
        return NULL;
    }

    // ensure mode is valid
    if (strcmp(mode, "r") != 0 && strcmp(mode, "w") != 0)
    {
        return NULL;
    }

    // allocate Huffile
    Huffile* hf = malloc(sizeof(Huffile));
    if (hf == NULL)
    {
        return NULL;
    }

    // open file
    hf->stream = fopen(path, mode);
    if (hf->stream == NULL)
    {
        free(hf);
        return NULL;
    }

    // remember mode
    hf->io = (strcmp(mode, "w") == 0) ? WRITE : READ;

    // remember size and final buffer's index if reading
    if (hf->io == READ)
    {
        // fast-forward to end of file
        if (fseek(hf->stream, -1, SEEK_END) != 0)
        {
            fclose(hf->stream);
            free(hf);
            return NULL;
        }

        // remember size
        if ((hf->size = ftell(hf->stream) + 1) == 0)
        {
            fclose(hf->stream);
            free(hf);
            return NULL;
        }

        // remember final buffer's index
        if (fread(&hf->zth, sizeof(hf->zth), 1, hf->stream) != 1)
        {
            fclose(hf->stream);
            free(hf);
            return NULL;
        }

        // rewind to start of file
        if (fseek(hf->stream, 0, SEEK_SET) != 0)
        {
            fclose(hf->stream);
            free(hf);
            return NULL;
        }
    }

    // initialize state
    hf->buffer = 0x00;
    hf->ith = 0;

    // return Huffile
    return hf;
}

/**
 * Reads in header if still at start of file.
 *
 * Returns true on success and false on failure (e.g., not at start of file).
 */
bool hread(Huffeader* h, Huffile* hf)
{
    // ensure destination and source aren't NULL
    if (h == NULL || hf == NULL)
    {
        return false;
    }

    // ensure we're still at start of file
    if (ftell(hf->stream) != 0)
    {
        return false;
    }

    // read in header
    if (fread(h, sizeof(Huffeader), 1, hf->stream) != 1)
    {
        return false;
    }

    // success!
    return true;
}

/**
 * Writes out header if still at start of file.
 *
 * Returns true on success and false on failure (e.g., not at start of file).
 */
bool hwrite(Huffeader* h, Huffile* hf)
{
    // ensure source and destination aren't NULL
    if (h == NULL || hf == NULL)
    {
        return false;
    }

    // ensure we're still at start of file
    if (ftell(hf->stream) != 0)
    {
        return false;
    }

    // write out header
    if (fwrite(h, sizeof(Huffeader), 1, hf->stream) != 1)
    {
        return false;
    }

    // success!
    return true;
}
