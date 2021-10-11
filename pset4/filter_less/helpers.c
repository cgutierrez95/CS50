#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;

    // Scan through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the RGB to make a grayscale
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

            avg = round(avg);

            //Replace the RGB values with the average.
            image[i][j].rgbtBlue = (int)avg;
            image[i][j].rgbtGreen = (int)avg;
            image[i][j].rgbtRed = (int)avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;

    // Scan through each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Calculate the sepia values for the RGB
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Substitute the RGB values with the sepia values.
            image[i][j].rgbtRed = (int) sepiaRed;
            image[i][j].rgbtGreen = (int) sepiaGreen;
            image[i][j].rgbtBlue = (int) sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    // Scan through each pixel row of the image
    for (int i = 0; i < height; i++)
    {
        // if columns are even
        if (width % 2 == 0)
        {
            // Switches pixels
            for (int j = 0; j < width / 2; j++)
            {
                temp = image[i][width - 1 - j];
                image[i][width - 1 - j] = image[i][j];
                image[i][j] = temp;
            }
        }
        // if columns are odd.
        else
        {
            //Switches pixels
            for (int j = 0; j < round((float)width / 2) - 1; j++)
            {
                temp = image[i][width - 1 - j];
                image[i][width - 1 - j] = image[i][j];
                image[i][j] = temp;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a copy from the original array.
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    float sumRed, sumGreen, sumBlue;

    int counter;

    // Scan through the each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;

            counter = 0;

            //Look for outside rows
            for (int r = -1; r < 2; r++)
            {
                if (i + r < 0 || i + r >= height)
                {
                    continue;
                }

                //Look for outside columns
                for (int c = -1; c < 2; c++)
                {
                    if (j + c < 0 || j + c >= width)
                    {
                        continue;
                    }

                    //Take the value of RGB of the temp array.
                    sumRed += temp[i + r][j + c].rgbtRed;
                    sumGreen += temp[i + r][j + c].rgbtGreen;
                    sumBlue += temp[i + r][j + c].rgbtBlue;

                    counter++;
                }
            }

            //Calculate the average
            sumRed = (int)round(sumRed / counter);
            sumGreen = (int)round(sumGreen / counter);
            sumBlue = (int)round(sumBlue / counter);

            //Update the pixel
            image[i][j].rgbtRed = sumRed;
            image[i][j].rgbtGreen = sumGreen;
            image[i][j].rgbtBlue = sumBlue;
        }
    }
    return;
}