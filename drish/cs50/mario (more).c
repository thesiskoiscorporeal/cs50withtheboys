#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //declare strings for pyramids heights 1 through 8
    string pyramid1 = ("#  #\n");
    string pyramid2 = (" #  #\n##  ##\n");
    string pyramid3 = ("  #  #\n ##  ##\n###  ###\n");
    string pyramid4 = ("   #  #\n  ##  ##\n ###  ###\n####  ####\n");
    string pyramid5 = ("    #  #\n   ##  ##\n  ###  ###\n ####  ####\n#####  #####\n");
    string pyramid6 = ("     #  #\n    ##  ##\n   ###  ###\n  ####  ####\n #####  #####\n######  ######\n");
    string pyramid7 = ("      #  #\n     ##  ##\n    ###  ###\n   ####  ####\n  #####  #####\n ######  ######\n#######  #######\n");
    string pyramid8 = ("       #  #\n      ##  ##\n     ###  ###\n    ####  ####\n   #####  #####\n  ######  ######\n #######  #######\n########  ########\n");
    //while loop that returns pyramid for input 1-8, else re-prompts
    while (true)
    {
        int height = get_int("Height: ");
        if (height == 1)
        {
            printf("%s", pyramid1);
            break;
        }
        else if (height == 2)
        {
            printf("%s", pyramid2);
            break;
        }
        else if (height == 3)
        {
            printf("%s", pyramid3);
            break;
        }
        else if (height == 4)
        {
            printf("%s", pyramid4);
            break;
        }
        else if (height == 5)
        {
            printf("%s", pyramid5);
            break;
        }
        else if (height == 6)
        {
            printf("%s", pyramid6);
            break;
        }
        else if (height == 7)
        {
            printf("%s", pyramid7);
            break;
        }
        else if (height == 8)
        {
            printf("%s", pyramid8);
            break;
        }
    }
}
