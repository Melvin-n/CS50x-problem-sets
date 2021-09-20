#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        //get the average of red green and blue values, divide by the number of values, avg number becomes number of rgb values
        {
            int avg = round((round(image[y][x].rgbtRed) + round(image[y][x].rgbtBlue) + round(image[y][x].rgbtGreen)) / 3);
            image[y][x].rgbtRed = avg;
            image[y][x].rgbtBlue = avg;
            image[y][x].rgbtGreen = avg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //use the formalu for calculating sepia values, cap it to 255
            int sepiaRed = round((0.393 * image[y][x].rgbtRed) + (0.769 * image[y][x].rgbtGreen) + (0.189 * image[y][x].rgbtBlue));
            int sepiaBlue = round((0.272 * image[y][x].rgbtRed) + (0.534 * image[y][x].rgbtGreen) + (0.131 * image[y][x].rgbtBlue));
            int sepiaGreen = round((0.349 * image[y][x].rgbtRed) + (0.686 * image[y][x].rgbtGreen) + (0.168 * image[y][x].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[y][x].rgbtRed = sepiaRed;
            image[y][x].rgbtBlue = sepiaBlue;
            image[y][x].rgbtGreen = sepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //for each value, swap it with the value that is opposite, using width minus an iterating value
    //even number width has one extra swap
    for (int y = 0; y <= height; y++)
    {
        if (width % 2 == 0)
        {
            for (int x = 0; x <= (width - 1) / 2; x++)
            {
                int newx = (width - 1) - x;

                int tempred = image[y][x].rgbtRed;
                int tempblue = image[y][x].rgbtBlue;
                int tempgreen = image[y][x].rgbtGreen;
                image[y][x].rgbtRed = image[y][newx].rgbtRed;
                image[y][newx].rgbtRed = tempred;
                image[y][x].rgbtBlue = image[y][newx].rgbtBlue;
                image[y][newx].rgbtBlue = tempblue;
                image[y][x].rgbtGreen = image[y][newx].rgbtGreen;
                image[y][newx].rgbtGreen = tempgreen;
            }
        }

        else
        {

            for (int x = 0; x <= floor(width / 2); x++)
            {
                int newxeven = width - x - 1;

                int tempred = image[y][x].rgbtRed;
                int tempblue = image[y][x].rgbtBlue;
                int tempgreen = image[y][x].rgbtGreen;
                image[y][x].rgbtRed = image[y][width - x - 1].rgbtRed;
                image[y][newxeven].rgbtRed = tempred;
                image[y][x].rgbtBlue = image[y][width - x - 1].rgbtBlue;
                image[y][newxeven].rgbtBlue = tempblue;
                image[y][x].rgbtGreen = image[y][width - x - 1].rgbtGreen;
                image[y][newxeven].rgbtGreen = tempgreen;

            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the image to retrieve the original rgb values from
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //make a case for all possibilites of where a pixel can be, one of four corners, one of four edges, or not touching an edge or corner
    //get the average of surrounding pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            if (y == 0 && x == 0)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x + 1].rgbtRed + copy[y + 1][x].rgbtRed + copy[y + 1][x + 1].rgbtRed) / (float)4);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y + 1][x + 1].rgbtBlue) / (float)4);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x + 1].rgbtGreen + copy[y + 1][x].rgbtGreen + copy[y + 1][x + 1].rgbtGreen) / (float)4);
            }

            else if (y == 0 && x == width - 1)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x - 1].rgbtRed + copy[y + 1][x].rgbtRed + copy[y + 1][x - 1].rgbtRed) / (float)4);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x - 1].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y + 1][x - 1].rgbtBlue) / (float)4);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x - 1].rgbtGreen + copy[y + 1][x].rgbtGreen + copy[y + 1][x - 1].rgbtGreen) / (float)4);
            }
            else if (y == height - 1 && x == 0)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x + 1].rgbtRed + copy[y - 1][x].rgbtRed + copy[y - 1][x + 1].rgbtRed) / (float)4);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y - 1][x].rgbtBlue + copy[y - 1][x + 1].rgbtBlue) / (float)4);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x + 1].rgbtGreen + copy[y - 1][x].rgbtGreen + copy[y - 1][x + 1].rgbtGreen) / (float)4);
            }
            else if (y == height - 1 && x == width - 1)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x - 1].rgbtRed + copy[y - 1][x].rgbtRed + copy[y - 1][x - 1].rgbtRed) / (float)4);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x - 1].rgbtBlue + copy[y - 1][x].rgbtBlue + copy[y - 1][x - 1].rgbtBlue) / (float)4);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x - 1].rgbtGreen + copy[y - 1][x].rgbtGreen + copy[y - 1][x - 1].rgbtGreen) / (float)4);
            }

            else if (x == 0)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x + 1].rgbtRed + copy[y - 1][x + 1].rgbtRed + copy[y + 1][x + 1].rgbtRed + copy[y + 1][x].rgbtRed + copy[y - 1][x].rgbtRed) / (float)6);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y - 1][x + 1].rgbtBlue + copy[y + 1][x + 1].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y - 1][x].rgbtBlue) / (float)6);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x + 1].rgbtGreen + copy[y - 1][x + 1].rgbtGreen + copy[y + 1][x + 1].rgbtGreen + copy[y + 1][x].rgbtGreen+ copy[y - 1][x].rgbtGreen) / (float)6);
            }

            else if (x == width - 1)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y][x - 1].rgbtRed + copy[y - 1][x - 1].rgbtRed + copy[y + 1][x - 1].rgbtRed + copy[y + 1][x].rgbtRed + copy[y - 1][x].rgbtRed) / (float)6);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y][x - 1].rgbtBlue + copy[y - 1][x - 1].rgbtBlue + copy[y + 1][x - 1].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y - 1][x].rgbtBlue) / (float)6);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y][x - 1].rgbtGreen + copy[y - 1][x - 1].rgbtGreen + copy[y + 1][x - 1].rgbtGreen + copy[y + 1][x].rgbtGreen+ copy[y - 1][x].rgbtGreen) / (float)6);
            }

            else if (y == 0)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y + 1][x].rgbtRed + copy[y + 1][x + 1].rgbtRed + copy[y + 1][x - 1].rgbtRed + copy[y][x + 1].rgbtRed + copy[y][x - 1].rgbtRed) / (float)6);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y + 1][x + 1].rgbtBlue + copy[y + 1][x - 1].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y][x - 1].rgbtBlue) / (float)6);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y + 1][x].rgbtGreen + copy[y + 1][x + 1].rgbtGreen + copy[y + 1][x - 1].rgbtGreen + copy[y][x + 1].rgbtGreen+ copy[y][x - 1].rgbtGreen) / (float)6);
            }

            else if (y == height - 1)
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y - 1][x].rgbtRed + copy[y - 1][x + 1].rgbtRed + copy[y - 1][x - 1].rgbtRed + copy[y][x + 1].rgbtRed + copy[y][x - 1].rgbtRed) / (float)6);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y - 1][x].rgbtBlue + copy[y - 1][x + 1].rgbtBlue + copy[y - 1][x - 1].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y][x - 1].rgbtBlue) / (float)6);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y - 1][x].rgbtGreen + copy[y - 1][x + 1].rgbtGreen + copy[y - 1][x - 1].rgbtGreen + copy[y][x + 1].rgbtGreen+ copy[y][x - 1].rgbtGreen) / (float)6);
            }

            else
            {
                image[y][x].rgbtRed = round((copy[y][x].rgbtRed + copy[y + 1][x].rgbtRed + copy[y + 1][x + 1].rgbtRed + copy[y + 1][x - 1].rgbtRed + copy[y][x + 1].rgbtRed + copy[y][x - 1].rgbtRed + copy[y - 1][x - 1].rgbtRed + copy[y - 1][x + 1].rgbtRed + copy[y - 1][x].rgbtRed) / (float)9);
                image[y][x].rgbtBlue = round((copy[y][x].rgbtBlue + copy[y + 1][x].rgbtBlue + copy[y + 1][x + 1].rgbtBlue + copy[y + 1][x - 1].rgbtBlue + copy[y][x + 1].rgbtBlue + copy[y][x - 1].rgbtBlue + copy[y - 1][x - 1].rgbtBlue + copy[y - 1][x + 1].rgbtBlue + copy[y - 1][x].rgbtBlue) / (float)9);
                image[y][x].rgbtGreen = round((copy[y][x].rgbtGreen + copy[y + 1][x].rgbtGreen + copy[y + 1][x + 1].rgbtGreen + copy[y + 1][x - 1].rgbtGreen + copy[y][x + 1].rgbtGreen + copy[y][x - 1].rgbtGreen + copy[y - 1][x - 1].rgbtGreen + copy[y - 1][x + 1].rgbtGreen + copy[y - 1][x].rgbtGreen) / (float)9);
            }
        }
    }
    return;
}
