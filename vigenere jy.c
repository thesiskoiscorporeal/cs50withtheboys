#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int shift(char c) // Nice function to convert
{
    if (c >= 'a' && c <= 'z') // For lowercase letters
    {
        return(c - 'a');
    }
    else if (c >= 'A' && c <= 'Z') // For uppercase letters
    {
        return(c - 'A');
    }
    else
    {
        return(c);
    }
}

int main(int argc, string argv[])
{
    if (argc == 2) // Checks that there are two arguments
    {
        for (int j = 0, n = strlen(argv[1]); j < n; j++) // Checks that argument is alphabet
        {
            if (isalpha(argv[1][j])) {}
            else
            {
                printf("Usage ./vigenere keyword\n");
                exit(1); // Ends program
            }
        }
        // Now I need to store it as an array of digits
        
        int length = strlen(argv[1]); // Finds length of cipher
        string input = get_string("plaintext: "); // Gets message to be encrypted
        
        printf("ciphertext: ");
        int counter = 0;
        for (int i = 0, n = strlen(input); i < n; i++) // Encrypts message
        {
            if (input[i] >= 'a' && input[i] <= 'z') // For lowercase letters
            {
                counter = counter + 1;
                printf("%c", (((input[i] + shift(argv[1][((counter - 1) % length)]) - 'a') % 26) + 'a'));
            }
            else if (input[i] >= 'A' && input[i] <= 'Z') // For uppercase letters
            {
                counter = counter + 1;
                printf("%c", (((input[i] + shift(argv[1][((counter - 1) % length)]) - 'A') % 26) + 'A'));
            }
            else // For non-letters
            {
                printf("%c", input[i]);
            }
        }
        printf("\n");
    }
    else // Ensures there is only one other argument
    {
        printf("Usage ./vigenere keyword\n");
        return (1);
    }
}
