#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

const int CONST_ALPHABET_SIZE = 26;

const int CONST_LOWER_OFFSET = 'a';
const int CONST_UPPER_OFFSET = 'A';

// Check the keyword for only alphabetic characters
bool check_keyword(char *str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
        if (!isalpha(str[i]))
            return false;
            
    return true;
}

// Gets a value from a key
int get_key(const char *key, int pos, int length)
{
    int i = pos % length;

    if (islower(key[i]))
        return key[i] - CONST_LOWER_OFFSET;
    else
        return key[i] - CONST_UPPER_OFFSET;
}

// Encodes the text with the Viginere cipher
// Accepts a plaintext string for input and a cipherkey
// Rewrites the string with an encoded one
void encode_viginere(char *str, const char *key)
{
    int key_length = strlen(key);
    
    // Encode each symbol of the text with the key
    for (int i = 0, k = 0, n = strlen(str); i < n; i++)
    {
        if (isalpha(str[i]))
        {
            if (islower(str[i]))
                str[i] = CONST_LOWER_OFFSET + (str[i] - CONST_LOWER_OFFSET + get_key(key, k, key_length)) % CONST_ALPHABET_SIZE;
            else if (isupper(str[i]))
                str[i] = CONST_UPPER_OFFSET + (str[i] - CONST_UPPER_OFFSET + get_key(key, k, key_length)) % CONST_ALPHABET_SIZE;
        
            k++;
        }
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
    
    // Check the correctness of the keyword
    if (!check_keyword(argv[1]))
    {
        printf("Incorrect command-line argument specified.\n");
        
        return 1;        
    }
    
    // Input a plaintext string    
    char *str = GetString();
    
    // Encode the text with the Viginere cipher
    encode_viginere(str, argv[1]);
    
    //Output the string
    printf("%s\n", str);
    
    // Free the memory
    free(str);
    
    return 0;
}
