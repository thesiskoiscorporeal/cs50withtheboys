#include <stdlib.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale //DONE
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed);
            int darkness = round(sum / 3);

            image[i][j].rgbtBlue = darkness;
            image[i][j].rgbtGreen = darkness;
            image[i][j].rgbtRed = darkness;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //establish floats for RGB values
            float oldRed = image[i][j].rgbtRed;
            float oldGreen = image[i][j].rgbtGreen;
            float oldBlue = image[i][j].rgbtBlue;

            //calculate new RGB values for sepia using floats rounded to nearest int
            int newBlue = round(.272 * oldRed + .534 * oldGreen + .131 * oldBlue);
            int newGreen = round(.349 * oldRed + .686 * oldGreen + .168 * oldBlue);
            int newRed = round(.393 * oldRed + .769 * oldGreen + .189 * oldBlue);

            //cap new RGB values to maximum of 255
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            if (newGreen > 255)
            {
                newGreen = 255;
            }

            if (newRed > 255)
            {
                newRed = 255;
            }

            //sets RGBTRIPLE to new values
            image[i][j].rgbtBlue = newBlue;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtRed = newRed;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //create new array image_dump to place new RGB values inside before copying over
    RGBTRIPLE(*image_dump)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //iterate over infile's pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find new RGB values
            image_dump[i][width - j - 1] = image[i][j]; // -1 to account for index being offset by -1
        }

    }

    //copy over RGBtriples from image_dump to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_dump[i][j];
        }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create new array image_dump to place new RGB values inside before copying over
    RGBTRIPLE(*image_dump)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    //iterate over infile pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //define floats for sum R/G/B of surrounding pixels
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;

            int counter = 0; //counter variable for number of surrounding pixels

            //iterate over surrounding pixels to obtain sum R/G/B
            for (int q = i - 1; q <= i + 1; q++)
            {
                for (int r = j - 1; r <= j + 1; r++)
                {
                    if (q >= 0 && q <= height - 1 && r >= 0 && r <= width - 1) //condition for valid pixels only
                    {
                        sumRed += image[q][r].rgbtRed;
                        sumGreen += image[q][r].rgbtGreen;
                        sumBlue += image[q][r].rgbtBlue;
                        counter++;
                    }
                }
            }

            //calculate and write new RGB triples to image_dump
            int newRed = round(sumRed / counter);
            int newGreen = round(sumGreen / counter);
            int newBlue = round(sumBlue / counter);

            image_dump[i][j].rgbtRed = newRed;
            image_dump[i][j].rgbtGreen = newGreen;
            image_dump[i][j].rgbtBlue = newBlue;
        }
    }

    //copy over RGBtriples from image_dump to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_dump[i][j];
        }

    }

    return;
}
