#include <cs50.h>
#include <stdio.h>
#include <math.h>

long get_positive_number (string prompt);
int check_length (long number);
bool check_valid (int length);
bool check_luhn (long number);

int main (void)
{
    long number = get_positive_number ("Credit Card Number: ");

    // Check that number is valid
    int length = check_length (number);

    // Check validity of length
    if (check_valid (length) == false)
    {
        printf ("INVALID\n");
    }

    // Check validity via Luhn
    else
    {
        if (check_luhn (number) == false)
        {
            printf ("INVALID\n");
        }

        // Sort to AMEX/MASTERCARD/VISA
        else
        {
            int x = 0;
            while (number > 99)
            {
                x = number / 10;
                number /= 10;
            }
            if (51 <= x && x <= 55)
            {
                printf ("MASTERCARD\n");
            }
            else if (x == 34 || x == 37)
            {
                printf ("AMEX\n");
            }
            else if (40 <= x && x <= 49)
            {
                printf ("VISA\n");
            }
            else
            {
                printf ("INVALID\n");
            }
        }
    }
}

// Obtain credit card number
long get_positive_number (string prompt)
{
    long n;
    do
    {
        n = get_long ("%s", prompt);
    }
    while (n <= 0);
    return n;
}

// Obtain credit card length
int check_length (long number)
{
    int length = 0;
    while (number > 0)
    {
        number /= 10;
        length++;
    }
    return length;
}

// Check if length is valid
bool check_valid (int length)
{
    if (length == 13 || length == 15 || length == 16)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

// Check via Luhn's algorithm
bool check_luhn (long number)
{
    int odd = 0;
    int even = 0;
    while (number>0)
    {
        // Summation of every (n)th, (n-2)th...
        int n1 = number % 10;
        odd += n1;
        number /= 10;

        // Summation of the digits of every (n-1)th, (n-3)th...
        int n2 = 2 * (number % 10);
        if (n2 >= 10)
        {
            even += (n2 % 10) + (n2 / 10);
        }
        else
        {
            even += n2;
        }
        number /= 10;
    }
    int sum = even + odd;
    sum %= 10;
    if (sum == 0)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}






