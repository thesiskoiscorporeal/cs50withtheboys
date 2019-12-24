#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{
    while (true)
    {
        float change = get_float("Change owed: ");
        int cents = round(change * 100);
        if (change >= 0)
        {
            int counter = 0;
            while  (cents - 25 >= 0)
            {
                counter = counter + 1;
                cents = cents - 25;
            }
            while  (cents - 10 >= 0)
            {
                counter = counter + 1;
                cents = cents - 10;
            }
            while  (cents - 5 >= 0)
            {
                counter = counter + 1;
                cents = cents - 5;
            }
            while  (cents - 1 >= 0)
            {
                counter = counter + 1;
                cents = cents - 1;
            }
            printf("%i\n", counter);
            break;
        }
    }
}
