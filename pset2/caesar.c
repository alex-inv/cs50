#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const int CONST_ALPHABET_SIZE = 26;

const int CONST_LOWER_OFFSET = 'a';
const int CONST_UPPER_OFFSET = 'A';

// Encodes the text with the Caesar cipher
// Accepts a plaintext string for input and a cipherkey
// Rewrites the string with an encoded one
void encode_caesar(char *str, int k)
{
    // Encode each symbol of the text with the key
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (islower(str[i]))
            str[i] = CONST_LOWER_OFFSET + (str[i] - CONST_LOWER_OFFSET + k) % CONST_ALPHABET_SIZE;
        else if (isupper(str[i]))
            str[i] = CONST_UPPER_OFFSET + (str[i] - CONST_UPPER_OFFSET + k) % CONST_ALPHABET_SIZE;
    }
}

int main(int argc, char *argv[])
{
    // Check the number of input parameters
    if (argc != 2)
    {
        printf("Incorrect number of command-line arguments specified.\n");
        
        return 1;
    }
    
    // Convert the input parameter to a number
    int k = atoi(argv[1]);
    
    // Input a plaintext string    
    char *str = GetString();
    
    // Encode the text with a Caesar cipher
    encode_caesar(str, k);
    
    //Output the string
    printf("%s\n", str);
    
    // Free the memory
    free(str);
    
    return 0;
}
