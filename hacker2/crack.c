#define _XOPEN_SOURCE
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int CONST_WORD_SIZE = 128;
const int CONST_MAX_PASSWD_SIZE = 8;

int seconds;    // To store amount of seconds needed to crack a password

// Encodes the word and compares it to original encrypted password
bool try_passwd(const char *plain, const char *cipher, const char *salt)
{
    if (!strcmp(crypt(plain, salt), cipher))
    {
        printf("Cracking succesful. Matching password - %s\n", plain);
        printf("Program executed in %d seconds.\n", (int) time(NULL) - seconds);
        
        return true;
    }
    
    return false;
}

// Deciphers the hashed password, and stores it into dest variable
bool dict_attack(const char *passwd, const char *salt)
{
    char cur_word[CONST_WORD_SIZE];
    FILE *f;
    
    // Prepare a dictionary
    f = fopen("/usr/share/dict/words", "r");
    
    if (!f)
    {
        printf("Error opening dictionary file.\n");
        
        return false;
    }
    
    // For each word in dictionary
    while (fgets(cur_word, CONST_WORD_SIZE, f))
    {
        cur_word[strlen(cur_word) - 1] = '\0';
        
        // Try currend word
        if (try_passwd(cur_word, passwd, salt))
            return true;
    }
    
    return false;
}

// Perform a brute-force attack on a password
bool brute_force(char *passwd, const char *salt)
{   
    char arr_chars[] = {"0123456789abcdefghijklmnopqrstuvwxyz"};
    //char arr_chars[] = {"0123456789AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz !\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"};
    
    int arr_length = strlen(arr_chars);
    
    char cur_word[CONST_MAX_PASSWD_SIZE + 1];
    int pos[CONST_MAX_PASSWD_SIZE];
    
    cur_word[CONST_MAX_PASSWD_SIZE] = '\0';    

    // Outer loop - controls word length
    for (int max_chars = 0; max_chars < CONST_MAX_PASSWD_SIZE; max_chars++)
    {
        printf("Trying length %d\n", max_chars + 1);
        
        bool loop_completed = false;
        
        // Initialize the word
        int idx;
        
        for (idx = 0; idx <= max_chars; idx++)
        {
            pos[idx] = 0;
            cur_word[idx] = arr_chars[pos[idx]];
        }
        
        cur_word[idx] = '\0';
    
        // Main brute-force loop
        // Ends when every symbol combination is checked
        while (!loop_completed)
        {
            // Try currend word
            if (try_passwd(cur_word, passwd, salt))
                return true;
        
            // One iteration of brute-force
            bool shift = true;
            
            for (int cur_char = 0; cur_char <= max_chars; cur_char++)
                // If shift - change character
                if (shift)
                {
                    // If all character are done
                    if (pos[cur_char] == arr_length - 1)
                    {
                        // If last symbol - loop is over
                        if (cur_char == max_chars)
                            loop_completed = true;
                        // Change to first symbol again
                        else
                        {
                            pos[cur_char] = 0;
                            cur_word[cur_char] = arr_chars[pos[cur_char]];
                        }
                    }
                    else
                    {
                        cur_word[cur_char] = arr_chars[++pos[cur_char]];
                        
                        shift = false;
                    }
                }
        }
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Incorrect number of parameters\n");
        
        return 1;
    }
    
    seconds = time(NULL);
    
    // Extract the salt from a source
    char salt[2];
    
    strncpy(salt, argv[1], 2);
    
    printf("Using dictionary attack...\n");
    
    // First do a dictionary-based attack
    if (dict_attack(argv[1], salt))
        return 0;
        
    printf("Dictionary attack failed. Using brute-force...\n");
        
    // Dictionary attack failed, prepare to do a brute-force attack
    if (brute_force(argv[1], salt))
        return 0;
        
    // Cracking failed
    printf("Encrypted key could not be deciphered.\n");
    
    return 0;
}
