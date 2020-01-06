#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_positive_float(string prompt);

int main(void)
{
    // get cash in dollars
    float cash = get_positive_float("Change owed: ");
    
    // convert float to integer (cents)
    int cents = round(cash*100);

    // greedy algorithim
    int coins[5] = {25,10,5,1};
    int i = 0;
    int x; // number of times cash can be divided by coin type
    int y = 0; // coins to be returned
    
    // loop for four types of coins
    for (i=0; i < 4;)
    {
        // y is only increased if remaining cash is more than coin type
        if (coins[i] <= cents)
        {
            x = cents/coins[i];
            y += x;
            cents -= coins[i]*x;
            i++;  
        }
        // skips coin type at [i] if remaining cash is less than coin type
        else if (coins[i] > cents)
        { 
            i++;
        }
    }
    // publish
    printf("Coins returned: %i\n", y);
}


//ensures cash is positive, else prompt again
float get_positive_float(string prompt)
{
    float n;
        do
        {
            n = get_float("%s", prompt);
        }
        while (n <= 0);
        return n;
}
