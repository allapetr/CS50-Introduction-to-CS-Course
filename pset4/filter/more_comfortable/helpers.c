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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3];
    int Gy[3][3];
    Gx[0][0] = Gx[2][0] = Gy[0][0] = Gy[0][2] = -1;
    Gx[0][1] = Gx[1][1] = Gx[2][1] = Gy[1][0] = Gy[1][1] = Gy[1][2] = 0;
    Gx[1][0] = Gy[0][1] = -2;
    Gx[0][2] = Gx[2][2] = Gy[2][0] = Gy[2][2] = 1;
    Gx[1][2] = Gy[2][1] = 2;

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
            int Gx_Red = 0;
            int Gx_Green = 0;
            int Gx_Blue = 0;

            int Gy_Red = 0;
            int Gy_Green = 0;
            int Gy_Blue = 0;
            for (int k = i - 1, p = 0; k <= i + 1; ++k, ++p)
            {
                for (int l = j - 1, q = 0; l <= j + 1; ++l, ++q)
                {
                    if (k < 0 || l < 0 || k > height - 1 || l > width - 1)
                    {
                        continue;
                    }

                    Gx_Red += image1[k][l].rgbtRed * Gx[p][q];
                    Gx_Green += image1[k][l].rgbtGreen * Gx[p][q];
                    Gx_Blue += image1[k][l].rgbtBlue * Gx[p][q];

                    Gy_Red += image1[k][l].rgbtRed * Gy[p][q];
                    Gy_Green += image1[k][l].rgbtGreen * Gy[p][q];
                    Gy_Blue += image1[k][l].rgbtBlue * Gy[p][q];
                }
            }
            int tempRed = round(sqrt(Gx_Red * Gx_Red + Gy_Red * Gy_Red));
            int tempGreen = round(sqrt(Gx_Green * Gx_Green + Gy_Green * Gy_Green));
            int tempBlue = round(sqrt(Gx_Blue * Gx_Blue + Gy_Blue * Gy_Blue));

            if (tempRed > 255)
            {
                tempRed = 255;
            }

            if (tempGreen > 255)
            {
                tempGreen = 255;
            }

            if (tempBlue > 255)
            {
                tempBlue = 255;
            }

            image[i][j].rgbtRed = tempRed;
            image[i][j].rgbtGreen = tempGreen;
            image[i][j].rgbtBlue = tempBlue;
        }
    }
}

