#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Gets a non-negative float from standard input
float read_input(const char *p_prompt)
{
    bool correct_input = false;
    float result;
    
    while (!correct_input)
    {
        printf("%s\n", p_prompt);
        result = GetFloat();
        
        if (result >= 0.0)
            correct_input = true;
    }
    
    return result;
}

// Returns the quotient of dividing a p_value by its p_factor.
// The p_value is then rewritten with its remainder.
int get_quotient(int *p_value, const int p_factor)
{
    int result;
    
    result = (*p_value) / p_factor;
    (*p_value) = (*p_value) % p_factor;
    
    return result;
}

int main(int argc, char *argv[])
{
    // Get the amount of change from user
    float amount;
    
    int cents_amount;
    int coins_total = 0;
        
    amount = read_input("O hai! How much change is owed?");
    
    // Convert the amount of money to integer value of total cents
    cents_amount = round(amount * 100);
    
    // Now check how much quarters, dimes and nickels are needed
    coins_total = coins_total + get_quotient(&cents_amount, 25);
    coins_total = coins_total + get_quotient(&cents_amount, 10);
    coins_total = coins_total + get_quotient(&cents_amount, 5);
    
    coins_total = coins_total + cents_amount;   // Only pennies are left
    
    // Now print the result
    printf("%d\n", coins_total);
    
    return 0;
}
