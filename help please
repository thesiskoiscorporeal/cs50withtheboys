#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string plaintext = get_string("Enter plaintext:\n");
    int key = get_int("Enter the key:\n");
    printf("Here is your ciphertext:\n");
    for (int i=0;i<strlen(plaintext);i+=1)
        {if ((int)plaintext[i]< 127-key)
            {printf("%c",((int) plaintext[i]+key));}
         else
            {printf("%c",((int) plaintext[i]-95+key));}
        }
    printf("\n");
}
