#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2) // Checks that there are two arguments
    {
        for (int j = 0, n = strlen(argv[1]); j < n; j++) // Checks that argument is integer
        {
            if (isdigit(argv[1][j])) {}
            else
            {
                printf("Usage ./caesar key\n");
                exit(0); // Ends program
            }
        }
        int cipher = atoi(argv[1]); // Stores cipher as integer data type
        string input = get_string("plaintext: "); // Gets message to be encrypted
        printf("ciphertext: ");
        for (int i = 0, n = strlen(input); i < n; i++) // Encrypts message
        {
            if (input[i] >= 'a' && input[i] <= 'z') // For lowercase letters
            {
                printf("%c", ((input[i] + cipher - 'a') % 26) + 'a');
            }
            else if (input[i] >= 'A' && input[i] <= 'Z') // For uppercase letters
            {
                printf("%c", ((input[i] + cipher - 'A') % 26) + 'A');
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
        printf("Usage ./caesar key\n");
        return(1);
    }
}
