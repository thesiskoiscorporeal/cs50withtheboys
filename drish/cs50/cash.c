#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    while(true) //set up a while loop so invalid inputs re-prompt the user
    { float rawfax = get_float("Change owed: ");
        if (rawfax > 0)
        {
            int counter = 0;
            int centsowed = round(rawfax * 100);
                for (; centsowed >= 25; counter++)
                        {
                            centsowed = centsowed - 25;             
                        }
                for (; centsowed >= 10; counter++)
                        {
                            centsowed = centsowed - 10;             
                        }
                for (; centsowed >= 5; counter++)
                        {
                            centsowed = centsowed - 5;             
                        }
                for (; centsowed >= 1; counter++)
                        {
                            centsowed = centsowed - 1;             
                        }
            printf("%i\n", counter);
            break;
                }        
        }
}
