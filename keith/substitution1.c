#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string key[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else for (int k = 0; k < 26; k += 1)//go through each letter of key
    {
        if (64 < (int) key[1][k] && (int) key [1][k] < 123)//if within letter range
        {
            if (90 < (int) key [1][k] && (int) key[1][k] < 97)//but in that small non letter region
            {
                printf("Key must contain 26 characters.\n");//reject
                return 1;
            }
            else if (97 < (int) key[1][k] && (int) key [1][k] < 123)//if lowercase
            {
                key[1][k] -= 32;//change to caps
            }
        }
        else//otherwise error
        {
            printf("Key must contain 26 characters.\n");
            return 1;//
        }
    int count = 0;
    for (int d = 0; d < 26; d += 1)//then compare against each letter of key
    {
        if (key[1][k] == key[1][d] || key[1][k] == key[1][d] + 32)
        {
            count += 1;
        }
    }
        if (count >= 2)//if duplicate letters
        {
            printf("Key must contain 26 characters.\n");
            return 1;//
        }
    }
    //if key is all ok then
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int p = 0; p < strlen(plaintext); p += 1)//go through each char of plaintext
    {
        if (64 < (int) plaintext[p] && (int) plaintext[p] < 91)//if plaintext char is uppercase
        {
            printf("%c", key [1] [(int) plaintext[p] - 65]);//print from key
        }
        else if (96 < (int) plaintext[p] && (int) plaintext[p] < 123)//if plaintext char is lowercase
        {
            printf("%c", key [1] [(int) plaintext[p] - 97] + 32);//print from key but convert to  lowercase first
        }
        else
        {
            printf("%c", plaintext [p]);//if not just print that char
        }
    }
    printf("\n");
    return 0;
}
