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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    //Create the G arrays.
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int SobelRed, SobelGreen, SobelBlue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    float sumRedGx, sumGreenGx, sumBlueGx, sumRedGy, sumGreenGy, sumBlueGy;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sumRedGx = 0;
            sumGreenGx = 0;
            sumBlueGx = 0;

            sumRedGy = 0;
            sumGreenGy = 0;
            sumBlueGy = 0;

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
                    sumRedGx += temp[i + r][j + c].rgbtRed * Gx[r + 1][c + 1];
                    sumGreenGx += temp[i + r][j + c].rgbtGreen * Gx[r + 1][c + 1];
                    sumBlueGx += temp[i + r][j + c].rgbtBlue * Gx[r + 1][c + 1];

                    sumRedGy += temp[i + r][j + c].rgbtRed * Gy[r + 1][c + 1];
                    sumGreenGy += temp[i + r][j + c].rgbtGreen * Gy[r + 1][c + 1];
                    sumBlueGy += temp[i + r][j + c].rgbtBlue * Gy[r + 1][c + 1];
                }
            }

            //Calculate the average
            SobelRed = (int)round(sqrt(pow(sumRedGx, 2) + pow(sumRedGy, 2)));
            SobelGreen = (int)round(sqrt(pow(sumGreenGx, 2) + pow(sumGreenGy, 2)));
            SobelBlue = (int)round(sqrt(pow(sumBlueGx, 2) + pow(sumBlueGy, 2)));

            //Cape to 255
            if (SobelRed > 255)
            {
                SobelRed = 255;
            }

            if (SobelGreen > 255)
            {
                SobelGreen = 255;
            }

            if (SobelBlue > 255)
            {
                SobelBlue = 255;
            }

            //Update the pixel
            image[i][j].rgbtRed = SobelRed;
            image[i][j].rgbtGreen = SobelGreen;
            image[i][j].rgbtBlue = SobelBlue;
        }
    }
    return;
}
