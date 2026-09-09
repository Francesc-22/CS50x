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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img_border[height+2][width+2];
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            img_border[i][j].rgbtRed = 0;
            img_border[i][j].rgbtGreen = 0;
            img_border[i][j].rgbtBlue = 0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img_border[i+1][j+1] = image[i][j];
        }
    }

    int Gx_red[height][width];
    int Gx_green[height][width];
    int Gx_blue[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a = i + 1;
            int b = j + 1;
            Gx_red[i][j] = round(-1 * img_border[a-1][b-1].rgbtRed + 1 * img_border[a-1][b+1].rgbtRed +
                                  -2 * img_border[a][b-1].rgbtRed + 2 * img_border[a][b+1].rgbtRed +
                                  -1 * img_border[a+1][b-1].rgbtRed + 1 * img_border[a+1][b+1].rgbtRed);
            Gx_green[i][j] = round(-1 * img_border[a-1][b-1].rgbtGreen + 1 * img_border[a-1][b+1].rgbtGreen +
                                    -2 * img_border[a][b-1].rgbtGreen + 2 * img_border[a][b+1].rgbtGreen +
                                    -1 * img_border[a+1][b-1].rgbtGreen + 1 * img_border[a+1][b+1].rgbtGreen);
            Gx_blue[i][j] = round(-1 * img_border[a-1][b-1].rgbtBlue + 1 * img_border[a-1][b+1].rgbtBlue +
                                    -2 * img_border[a][b-1].rgbtBlue + 2 * img_border[a][b+1].rgbtBlue +
                                    -1 * img_border[a+1][b-1].rgbtBlue + 1 * img_border[a+1][b+1].rgbtBlue);
        }
    }

    int Gy_red[height][width];
    int Gy_green[height][width];
    int Gy_blue[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int a = i + 1;
            int b = j + 1;
            Gy_red[i][j] = round(-1 * img_border[a-1][b-1].rgbtRed - 2 * img_border[a-1][b].rgbtRed - 1 * img_border[a-1][b+1].rgbtRed +
                                      1 * img_border[a+1][b-1].rgbtRed + 2 * img_border[a+1][b].rgbtRed + 1 * img_border[a+1][b+1].rgbtRed);
            Gy_green[i][j] = round(-1 * img_border[a-1][b-1].rgbtGreen - 2 * img_border[a-1][b].rgbtGreen - 1 * img_border[a-1][b+1].rgbtGreen +
                                        1 * img_border[a+1][b-1].rgbtGreen + 2 * img_border[a+1][b].rgbtGreen + 1 * img_border[a+1][b+1].rgbtGreen);
            Gy_blue[i][j] = round(-1 * img_border[a-1][b-1].rgbtBlue - 2 * img_border[a-1][b].rgbtBlue - 1 * img_border[a-1][b+1].rgbtBlue +
                                       1 * img_border[a+1][b-1].rgbtBlue + 2 * img_border[a+1][b].rgbtBlue + 1 * img_border[a+1][b+1].rgbtBlue);

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = round(sqrt(Gx_red[i][j] * Gx_red[i][j] + Gy_red[i][j] * Gy_red[i][j]));
            int green = round(sqrt(Gx_green[i][j] * Gx_green[i][j] + Gy_green[i][j] * Gy_green[i][j]));
            int blue = round(sqrt(Gx_blue[i][j] * Gx_blue[i][j] + Gy_blue[i][j] * Gy_blue[i][j]));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }

    return;
}
