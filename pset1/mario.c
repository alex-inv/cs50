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

// Draws a canonical Mario pyramid on-screen
// Has no checks for correctness of an input parameter - assumes they are done before
void draw_pyramid(const int p_height)
{
    char *s;
    
    // Allocate memory for a string - additional 2 chars for pyramid endind block and NIL char
    s = (char *)malloc(p_height + 2);

    // For each pyramid level
    for (int i = 0; i < p_height; i++)
    {
        //Empty the string
        strcpy(s, "");
        
        // Construct a corresponding C string - first spaces
        for (int j = 0; j < p_height - (i + 1); j++)
            strcat(s, " ");
        // Then hashes 
        for (int j = 0; j < i + 2; j++)
            strcat(s, "#");
            
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
