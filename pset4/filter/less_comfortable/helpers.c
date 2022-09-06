#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

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

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0, k = width - 1; j < k; ++j, --k)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create copy of array
    RGBTRIPLE image1[1000][1000];

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            image1[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if (i == 0 && j == 0)//Top left corner
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j + 1].rgbtRed + image1[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j + 1].rgbtGreen + image1[i][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j + 1].rgbtBlue + image1[i][j + 1].rgbtBlue) / 4.0);
            }
            else if (i == height - 1 && j == 0)//Bottom left corner
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[height - 2][j].rgbtRed + image1[height - 2][j + 1].rgbtRed + image1[height - 1][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[height - 2][j].rgbtGreen + image1[height - 2][j + 1].rgbtGreen + image1[height - 1][j + 1].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[height - 2][j].rgbtBlue + image1[height - 2][j + 1].rgbtBlue + image1[height - 1][j + 1].rgbtBlue) / 4.0);
            }
            else if (i == height - 1 && j == width - 1)//Bottom right corner
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[height - 2][width - 1].rgbtRed + image1[height - 2][width - 2].rgbtRed + image1[height - 1][width - 2].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[height - 2][width - 1].rgbtGreen + image1[height - 2][width - 2].rgbtGreen + image1[height - 1][width - 2].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[height - 2][width - 1].rgbtBlue +
                                            image1[height - 2][width - 2].rgbtBlue + image1[height - 1][width - 2].rgbtBlue) / 4.0);
            }
            else if (i == 0 && j == width - 1)//Top right corner
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i + 1][width - 1].rgbtRed + image1[i + 1][width - 2].rgbtRed + image1[i][width - 2].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i + 1][width - 1].rgbtGreen + image1[i + 1][width - 2].rgbtGreen + image1[i][width - 2].rgbtGreen) / 4.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i + 1][width - 1].rgbtBlue + image1[i + 1][width - 2].rgbtBlue + image1[i][width - 2].rgbtBlue) / 4.0);
            }
            else if (i == 0)//Top edge pixels
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j + 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i][j - 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j + 1].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i][j - 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j + 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i][j - 1].rgbtBlue) / 6.0);

            }
            else if (i == height - 1)//Bottom edge pixels
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i][j - 1].rgbtRed + image1[i - 1][j - 1].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j + 1].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i - 1][j - 1].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j + 1].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i - 1][j - 1].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j + 1].rgbtBlue) / 6.0);
            }
            else if (j == 0)//Left edge pixels
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j + 1].rgbtRed + image1[i + 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j + 1].rgbtGreen + image1[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j + 1].rgbtBlue + image1[i + 1][j].rgbtBlue) / 6.0);
            }
            else if (j == width - 1)//Right edge pixels
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j - 1].rgbtRed + image1[i][j - 1].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i + 1][j].rgbtRed) / 6.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j - 1].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i + 1][j].rgbtGreen) / 6.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j - 1].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i + 1][j].rgbtBlue) / 6.0);
            }
            else
            {
                image[i][j].rgbtRed = round((image1[i][j].rgbtRed + image1[i - 1][j].rgbtRed + image1[i - 1][j + 1].rgbtRed + image1[i][j + 1].rgbtRed + image1[i + 1][j + 1].rgbtRed + image1[i + 1][j].rgbtRed + image1[i + 1][j - 1].rgbtRed + image1[i][j - 1].rgbtRed + image1[i - 1][j - 1].rgbtRed) / 9.0);
                image[i][j].rgbtGreen = round((image1[i][j].rgbtGreen + image1[i - 1][j].rgbtGreen + image1[i - 1][j + 1].rgbtGreen + image1[i][j + 1].rgbtGreen + image1[i + 1][j + 1].rgbtGreen + image1[i + 1][j].rgbtGreen + image1[i + 1][j - 1].rgbtGreen + image1[i][j - 1].rgbtGreen + image1[i - 1][j - 1].rgbtGreen) / 9.0);
                image[i][j].rgbtBlue = round((image1[i][j].rgbtBlue + image1[i - 1][j].rgbtBlue + image1[i - 1][j + 1].rgbtBlue + image1[i][j + 1].rgbtBlue + image1[i + 1][j + 1].rgbtBlue + image1[i + 1][j].rgbtBlue + image1[i + 1][j - 1].rgbtBlue + image1[i][j - 1].rgbtBlue + image1[i - 1][j - 1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}
