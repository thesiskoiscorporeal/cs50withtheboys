#include <cs50.h>
#include <stdio.h>

int get_positive_integer(string prompt);

int main(void)
{
    int row, space, symbolL, symbolR;
    int totalR = get_positive_integer("Height: \n");
    
    for(row=1; row<=totalR; row++)
    {
        //print the spaces on the left
        for(space=1; space<=(totalR-row); space++)
            printf(" ");
        
        //print the left side
        for(symbolL=1; symbolL<=row; symbolL++)
            printf("#");
        
        //print the two spaces
        printf("  ");
        
        //print the right side
        for(symbolR=1; symbolR<=row; symbolR++)
            printf("#");
        
        //add a line to prep for next row
        printf("\n");
    }
    
}


//ensuring input is from 1 to 8
int get_positive_integer(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n>8 || n<1);
    return n;
}
