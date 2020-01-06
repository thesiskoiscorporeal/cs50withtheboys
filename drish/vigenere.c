#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int shift(char c);

int main(int argc, string argv[])
{  
    if (argc == 2)
    {
        //validate string input argv[1] consists of alphabets only
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (isalpha(argv[1][i]))
            {
                continue;
            }
            else
            {
                printf("Usage: ./vigenere keyword\n");
                return (1);
                break;
            }
        }
    }
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return (1);
    }
    
    //prompt user for plaintext string
    string ptext = get_string("plaintext: ");
    string ctext = ptext;
    
    //establish counter for keyword shift
    int j = 0; 
        
    //generate ciphertext
    for (int i = 0, len = strlen(ptext); i < len; i++)
    {
        int key = shift(argv[1][j]); //set value of key for each iteration
           
        if (isupper(ptext[i]))
        {
            ctext[i] = (((ptext[i] - 65) + key) % 26) + 65;
            
            //cycle counter value if char isupper
            if (j < strlen(argv[1]) - 1)
            {
                j++;
            }
            
            else
            {
                j = 0;
            }
        }
        
        else if (islower(ptext[i]))
        {
            ctext[i] = (((ptext[i] - 97) + key) % 26) + 97;
            
            //cycle counter value if char islower
            if (j < strlen(argv[1]) - 1)
            {
                j++; //increment counter if counter is less than length of keyword - 1
            }
            
            else
            {
                j = 0; //reset counter to 0 if counter is equal to length of keyword - 1 (and thus pointing to the final character)
            }
        }
    }
    
    //print ciphertext
    printf("ciphertext: %s\n", ctext);
    return (0);
}

//define shift function
int shift(char c)
{
    if (isupper(c))
    {
        int shiftvalue = c - 65;
        return shiftvalue;
    }
    
    else
    {
        int shiftvalue = c - 97;
        return shiftvalue;
    }
}
