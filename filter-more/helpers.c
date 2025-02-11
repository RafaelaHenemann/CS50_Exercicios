#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    int new = 0;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            new = round(sum / 3.0);
            // Update pixel values
            image[i][j].rgbtRed = new;
            image[i][j].rgbtGreen = new;
            image[i][j].rgbtBlue = new;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
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

    // Iterate for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare variables for colors and neighbors
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // Iterate for neighbors
            for (int hi = -1; hi <= 1; hi++)
            {
                for (int wj = -1; wj <= 1; wj++)
                {
                    int pi = i + hi;
                    int pj = j + wj;

                    // Verify edges and corners
                    if (pi >= 0 && pi < height && pj >= 0 && pj < width)
                    {
                        sumRed += copy[pi][pj].rgbtRed;
                        sumGreen += copy[pi][pj].rgbtGreen;
                        sumBlue += copy[pi][pj].rgbtBlue;
                        count++;
                    }
                }
            }
            // Update pixels values
            image[i][j].rgbtRed = round((float) sumRed / count);
            image[i][j].rgbtGreen = round((float) sumGreen / count);
            image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Iterate for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Declare variables for Gx and Gy colors
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            // Declare Sobel's mask
            int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            // Iterate for neighbors
            for (int hi = -1; hi <= 1; hi++)
            {
                for (int wj = -1; wj <= 1; wj++)
                {
                    int pi = i + hi;
                    int pj = j + wj;

                    // Verify edges and corners
                    RGBTRIPLE currentPixel = {0, 0, 0};
                    if (pi >= 0 && pi < height && pj >= 0 && pj < width)
                    {
                        currentPixel = copy[pi][pj];
                    }

                    // Apply Sobel's mask
                    GxRed += currentPixel.rgbtRed * Gx[hi + 1][wj + 1];
                    GxGreen += currentPixel.rgbtGreen * Gx[hi + 1][wj + 1];
                    GxBlue += currentPixel.rgbtBlue * Gx[hi + 1][wj + 1];

                    GyRed += currentPixel.rgbtRed * Gy[hi + 1][wj + 1];
                    GyGreen += currentPixel.rgbtGreen * Gy[hi + 1][wj + 1];
                    GyBlue += currentPixel.rgbtBlue * Gy[hi + 1][wj + 1];
                }
            }
            // New color values
            int newRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            int newGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int newBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));

            // Limit to 255
            if (newRed > 255)
            {
                newRed = 255;
            }
            if (newGreen > 255)
            {
                newGreen = 255;
            }
            if (newBlue > 255)
            {
                newBlue = 255;
            }

            // Update pixel value in the image
            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }
    return;
}
