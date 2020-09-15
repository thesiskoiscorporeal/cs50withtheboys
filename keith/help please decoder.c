#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    int key=get_int("Enter the key\n");
    string ciphertext=get_string("Enter the ciphertext\n");
    printf("Here is your deciphered text:\n");
    for (int i=0;i<strlen(ciphertext);i+=1)
        {if ((int)ciphertext[i]>61)
            {printf("%c",((int) ciphertext[i]-key));}
         else
            {printf("%c",((int)ciphertext[i]+95-key));}
        }
    printf("\n");
}
