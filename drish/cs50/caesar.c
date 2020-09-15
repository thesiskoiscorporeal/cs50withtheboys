#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{  
    if (argc == 2)
    {
        //validate string input argv[1] consists of digits only
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (isdigit(argv[1][i]))
            {
                continue;
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return (1);
                break;
            }
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return (1);
    }
    
    //convert string argv[1] into int
    int key = atoi(argv[1]);
    
    //prompt user for plaintext string
    string ptext = get_string("plaintext: ");
    string ctext = ptext;
    
    //generate ciphertext
    for (int i = 0, len = strlen(ptext); i < len; i++)
    {
        if (isupper(ptext[i]))
        {
            ctext[i] = (((ptext[i] - 65) + key) % 26) + 65;
        }
        
        else if (islower(ptext[i]))
        {
            ctext[i] = (((ptext[i] - 97) + key) % 26) + 97;
        }
    }
    
    //print ciphertext
    printf("ciphertext: %s\n", ctext);
}
