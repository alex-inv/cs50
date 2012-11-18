#include <stdio.h>
#include <cs50.h>
#include <string.h>

const int CONST_HEIGHT_MAX = 23;

// Gets an integer within specified limits (p_min and p_max parameters) from standard input
int read_height(const char *p_prompt, const int p_min, const int p_max)
{
    bool correct_input = false;
    int result;
    
    while (!correct_input)
    {
        printf("%s", p_prompt);
        result = GetInt();
        
        if (result >= p_min && result <= p_max)
            correct_input = true;
    }
    
    return result;
}

// Adds a p_amount of p_source strings to a p_dest string
// User must check the size limit of a p_dest string
void add_symbols(char *p_dest, const char *p_source, const int p_amount)
{
    for (int i = 0; i < p_amount; i++)
        strcat(p_dest, p_source);
}

// Draws a Mario double-pyramid on-screen
// Has no checks for correctness of an input parameter - assumes they are done before
void draw_pyramid(const int p_height)
{
    char *s;
    
    // Allocate memory for a string - 2 times p_height + 2 for gap + 1 for NIL char
    s = (char *)malloc(2 * p_height + 3);

    // For each pyramid level
    for (int i = 0; i < p_height; i++)
    {
        //Empty the string
        strcpy(s, "");
        
        // Construct a corresponding C string
        add_symbols(s, " ", p_height - (i + 1)); // Leading spaces
        add_symbols(s, "#", i + 1); // First half-pyramid
        add_symbols(s, " ", 2); // Gap
        add_symbols(s, "#", i + 1); // Last half-pyramid
            
        // Draw it on the screen
        printf("%s\n", s);
    }
    
    free(s);
}

int main(int argc, char *argv[])
{
    // Get the pyramid height from user
    int height;
    height = read_height("Height: ", 0, CONST_HEIGHT_MAX);
    
    // Output the pyramid to standard output
    draw_pyramid(height);
    
    return 0;
}
