#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
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

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
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
    for(int y = 0; y <= height; y++)
    {
        if(width % 2 == 0)
        {
            for(int x = 0; x <= (width - 1) / 2; x++)
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

            for(int x = 0; x <= floor(width / 2); x++)
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
    for(int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (y == 0 && x == 0)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y+ 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed) / 4);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y+ 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue) / 4);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y+ 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen) / 4);
            }
            
            else if (y == 0 && x == width)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x - 1].rgbtRed) / 4);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x - 1].rgbtBlue) / 4);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x - 1].rgbtGreen) / 4); 
            }
            else if (y == height && x == 0)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed) / 4);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue) / 4);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen) / 4); 
            }
            else if (y == height && x == width)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x - 1].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x - 1].rgbtRed) / 4);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x - 1].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x - 1].rgbtBlue) / 4);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x - 1].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x - 1].rgbtGreen) / 4); 
            }
            
            else if (x == 0)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x + 1].rgbtRed + image[y - 1][x + 1].rgbtRed + image[y + 1][x + 1].rgbtRed + image[y + 1][x].rgbtRed + image[y - 1][x].rgbtRed) / 6);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x + 1].rgbtBlue + image[y - 1][x + 1].rgbtBlue + image[y + 1][x + 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y - 1][x].rgbtBlue) / 6);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x + 1].rgbtGreen + image[y - 1][x + 1].rgbtGreen + image[y + 1][x + 1].rgbtGreen + image[y + 1][x].rgbtGreen+ image[y - 1][x].rgbtGreen) / 6);
            }
            
            else if (x == width)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y][x - 1].rgbtRed + image[y - 1][x - 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y + 1][x].rgbtRed + image[y - 1][x].rgbtRed) / 6);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y][x - 1].rgbtBlue + image[y - 1][x - 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y + 1][x].rgbtBlue + image[y - 1][x].rgbtBlue) / 6);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y][x - 1].rgbtGreen + image[y - 1][x - 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y + 1][x].rgbtGreen+ image[y - 1][x].rgbtGreen) / 6);
            }
            
            else if (y == 0)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y][x + 1].rgbtRed + image[y][x - 1].rgbtRed) / 6);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y][x + 1].rgbtBlue + image[y][x - 1].rgbtBlue) / 6);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y][x + 1].rgbtGreen+ image[y][x - 1].rgbtGreen) / 6);
            }
            
            else if (y == height)
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y - 1][x].rgbtRed + image[y - 1][x + 1].rgbtRed + image[y - 1][x - 1].rgbtRed + image[y][x + 1].rgbtRed + image[y][x - 1].rgbtRed) / 6);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y - 1][x].rgbtBlue + image[y - 1][x + 1].rgbtBlue + image[y - 1][x - 1].rgbtBlue + image[y][x + 1].rgbtBlue + image[y][x - 1].rgbtBlue) / 6);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y - 1][x].rgbtGreen + image[y - 1][x + 1].rgbtGreen + image[y - 1][x - 1].rgbtGreen + image[y][x + 1].rgbtGreen+ image[y][x - 1].rgbtGreen) / 6);
            }
            
            else 
            {
                image[y][x].rgbtRed = round((image[y][x].rgbtRed + image[y + 1][x].rgbtRed + image[y + 1][x + 1].rgbtRed + image[y + 1][x - 1].rgbtRed + image[y][x + 1].rgbtRed + image[y][x - 1].rgbtRed + + image[y - 1][x - 1].rgbtRed + image[y - 1][x + 1].rgbtRed + image[y - 1][x].rgbtRed  ) / 9);
                image[y][x].rgbtBlue = round((image[y][x].rgbtBlue + image[y + 1][x].rgbtBlue + image[y + 1][x + 1].rgbtBlue + image[y + 1][x - 1].rgbtBlue + image[y][x + 1].rgbtBlue + image[y][x - 1].rgbtBlue+  + image[y - 1][x - 1].rgbtRed + image[y - 1][x + 1].rgbtRed + image[y - 1][x].rgbtRed ) / 9);
                image[y][x].rgbtGreen = round((image[y][x].rgbtGreen + image[y + 1][x].rgbtGreen + image[y + 1][x + 1].rgbtGreen + image[y + 1][x - 1].rgbtGreen + image[y][x + 1].rgbtGreen+ image[y][x - 1].rgbtGreen +  + image[y - 1][x - 1].rgbtRed + image[y - 1][x + 1].rgbtRed + image[y - 1][x].rgbtRed ) / 9);
            }
        }
    }
    return;
}
