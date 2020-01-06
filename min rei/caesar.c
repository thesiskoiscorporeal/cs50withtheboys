#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool check (int argc, string num);
void caesar_key (string pt, int key);

int main (int argc, string argv[])
{
    // Makes func (check) work; idk why either pls help
    string num = (string) argv[1];
    
    // Func (check)
    if (check (argc, num) == false)
    {
        printf("./caesar key\n");
        return 1;
    }
    else
    {
        // Convert num to integer
        int key = atoi(num);
        
        // Obtain plain text
        string pt = get_string ("plaintext: ");
        
        // Caesar key (output cipher text)
        caesar_key (pt, key);
    }
}

// Checking
bool check (int argc, string num)
{
    if (argc == 2)
    {
        //ensure argv[1] == integer
        for (int i = 0, n = strlen(num); i < n; i++)
        {
            if (isdigit(num[i]))
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

// Caesar key
void caesar_key (string pt, int key)
{
    // establishing string ciphertext ("ct") of similar length to pt
    string ct = pt;
        
    // reiterate through plain text
    for (int i = 0, n = strlen(pt); i < n; i++)
    {
        // if uppercase
        if (isupper(pt[i]))
        {
            ct[i] = ((pt[i] - 65 + key) % 26) + 65;
            
        // if lowercase
        }
        else if (islower(pt[i]))
        {
            ct[i] = ((pt[i] - 97 + key) % 26) + 97;
        }
    }
    
    // publish
    printf ("ciphertext: %s\n", ct);
}

