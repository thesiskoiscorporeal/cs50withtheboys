#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool check(int argc, string input);
int shift(char c);
void vigenere_key(string pt, string input);

int main(int argc, string argv[])
{
    // Setting global variable argv[1]
    string input = argv[1];

    // Checking
    if (check(argc, input) == false)
    {
        printf("./vigenere keyword\n");
        return 1;
    }

    // Obtain plain text
    string pt = get_string("plaintext: ");

    // Vigenere key
    vigenere_key(pt, input);

}




// Checking function
bool check(int argc, string input)
{
    // Ensures single command-line argument, else false
    if (argc == 2)
    {
        // Ensures input consists solely of alphabtic charcters
        for (int i = 0, len = strlen(input); i < len; i++)
        {
            if (isalpha(input[i]))
            {
                continue;
            }
            else
            {
                return (false);
                break;
            }
        }
        return (true);
    }
    else
    {
        return (false);
    }
}

// Shift function
int shift(char c)
{
    int n = 0;
    if (isupper(c))
    {
        n = c - 65;
        return n;
    }
    else
    {
        n = c - 97;
        return n;
    }
}

// Vigenere key
void vigenere_key(string pt, string input)
{
    // Initialize string ciphertext ("ct") of similar length to pt
    string ct = pt;

    // Initialize character count in plaintext
    int counter_pt = 0;

    // Initiliaze length of input
    int len_input = strlen(input);

    // Establish loop through plaintext array
    for (int i = 0, len_pt = strlen(pt); i < len_pt; i++)
    {
        // Obtaining index value
        int index = counter_pt % len_input;

        // Calculating the key (integer form)
        int key = shift(input[index]);

        // Encrypting
        if (isupper(pt[i]))
        {
            ct[i] = ((pt[i] - 65 + key) % 26) + 65;
            counter_pt ++;
        }
        else if (islower(pt[i]))
        {
            ct[i] = ((pt[i] - 97 + key) % 26) + 97;
            counter_pt ++;
        }
    }

    // Publish
    printf("ciphertext: %s\n", ct);
}
