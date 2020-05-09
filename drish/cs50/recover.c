#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

//function prototypes
bool jpegchecker(BYTE *tocheck);

int main(int argc, char *argv[])
{
    //checks if exactly 2 arguments passed
    if (argc != 2)
    {
        printf("Usage: ./recover <file.raw>\n");
        return 1;
    }

    //opens file to pointer infile
    FILE *infile = fopen(argv[1], "r");

    //checks if fopen returns NULL
    if (infile == NULL)
    {
        printf("File %s could not be opened.\n", argv[1]);
        return 1;
    }

    BYTE *buffer = malloc(512); //allocate buffer
    char filename[50]; //declare array filename
    int filenumber = 0; //declare filenumber, set to 0
    size_t bytesread = 512; //declare variable bytesread, and set to 512

    while (bytesread == 512) //while 512 bytes are read from infile (i.e. not at the end)
    {
        if (jpegchecker(buffer) == true) //if current buffer is start of jpeg, create and write to new jpeg file
        {
            sprintf(&filename[0], "%03i.jpg", filenumber); //print current filename to string
            filenumber++; //increment filenumber
            FILE *img = fopen(filename, "w"); //open file pointer for image, with current filename

            //write 512 byte chunks to img
            do
            {
                fwrite(buffer, 1, 512, img);
                bytesread = fread(buffer, 1, 512, infile); //set value of bytesread (to check if at end of infile)
            }
            while (!jpegchecker(buffer) && bytesread == 512);   //while new jpeg signature not found, and not at end of file

            fclose(img); //close current image file pointer
        }

        //read 512 bytes to buffer
        else if (jpegchecker(buffer) == false)
        {
            bytesread = fread(buffer, 1, 512, infile); //set value of bytesread (to check if at end of infile)
        }
    }

    //free memory
    free(buffer);

    //close file pointers
    fclose(infile);
}

//function definitions
bool jpegchecker(BYTE *tocheck)
{
    if (tocheck[0] == 0xff && tocheck[1] == 0xd8 && tocheck[2] == 0xff)
    {
        if ((tocheck[3] & 0xf0) == 0xe0) //bitwise AND operator used
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    else
    {
        return false;
    }
}
