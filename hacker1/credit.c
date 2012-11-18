#include <stdio.h>
#include <cs50.h>
#include <string.h>

const int CONST_MAX_CARD_NUM = 16;

// Gets a non-negative long long from standard input
long long read_card_num(const char *p_prompt)
{
    bool correct_input = false;
    long long result;
    
    while (!correct_input)
    {
        printf("%s", p_prompt);
        result = GetLongLong();
        
        if (result >= 0)
            correct_input = true;
    }
    
    return result;
}

int sum_digits(int p_digit)
{
    return (p_digit / 10) + (p_digit % 10);
}

// Runs a Luhn algorithm to check a validity of a card number
bool check_valid(char *p_number)
{
    int digit;
    bool odd = true;
    
    int sum = 0;

    // Run backwards from the last character
    for (int i = strlen(p_number) - 1; i >= 0; i--)
    {
        digit = p_number[i] - '0';
    
        sum += odd? digit : sum_digits(digit * 2);
        odd = !odd;
    }
    
    // If congruent to modulo 10 - correct
    if (!(sum % 10))
        return true;
    else
        return false;
}

int main(int argc, char *argv[])
{
    // Get the credit card number from user
    long long card_num;
    card_num = read_card_num("Number: ");
    
    // Convert the card number to a string of digits
    char card_str[CONST_MAX_CARD_NUM];
    sprintf(card_str, "%lld", card_num);
    
    // Now check for card number types
    if (card_str[0] == '4' && check_valid(card_str))
        printf("VISA\n"); 
    else if (card_str[0] == '3' && (card_str[1] == '4' || card_str[1] == '7') && check_valid(card_str))
        printf("AMEX\n");
    else if (card_str[0] == '5' && (card_str[1] >= '1' || card_str[1] <= '5') && check_valid(card_str))
        printf("MASTERCARD\n");
    else
        printf("INVALID\n");
    
    return 0;
}
