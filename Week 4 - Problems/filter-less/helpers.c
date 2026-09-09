#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            int sepiaRed = round((0.393*image[i][j].rgbtRed + 0.769*image[i][j].rgbtGreen + 0.189*image[i][j].rgbtBlue) / 3.0);
            int sepiaGreen = round((0.349*image[i][j].rgbtRed + 0.686*image[i][j].rgbtGreen + 0.168*image[i][j].rgbtBlue) / 3.0);
            int sepiaBlue = round((0.272*image[i][j].rgbtRed + 0.534*image[i][j].rgbtGreen + 0.131*image[i][j].rgbtBlue) / 3.0);
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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;
            int count = 0;

            if (i == 0 && j == 0) // Top-left corner
            {
                redSum += copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                count = 4;
            }
            else if (i == 0 && j == width - 1) // Top-right corner
            {
                redSum += copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue;
                count = 4;
            }
            else if (i == height - 1 && j == width - 1) // Bottom-right corner
            {
                redSum += copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue;
                count = 4;
            }
            else if (i == height - 1 && j == 0) // Bottom-left corner
            {
                redSum += copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                count = 4;
            }
            else if (i == 0) // Top edge
            {
                redSum += copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                count = 6;
            }
            else if (i == height - 1) // Bottom edge
            {
                redSum += copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j -   1].rgbtRed + copy[i - 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue;
                count = 6;
            }
            else if (j == 0) // Left edge
            {
                redSum += copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                count = 6;
            }
            else if (j == width - 1) // Right edge
            {
                redSum += copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue;
                count = 6;
            }
            else // Middle pixels
            {
                redSum += copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                          copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                          copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed;
                greenSum += copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen +
                            copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                            copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen;
                blueSum += copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue;
                count = 9;
            }

            // Calculate average color values
            image[i][j].rgbtRed = round((float)redSum / count);
            image[i][j].rgbtGreen = round((float)greenSum / count);
            image[i][j].rgbtBlue = round((float)blueSum / count);
        }
    }

}
