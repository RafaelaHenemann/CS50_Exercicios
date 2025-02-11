#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create buffer
    uint8_t buffer[512];

    // While there's still data
    char filename[8];
    int c = 0;
    FILE *img = NULL;
    while (fread(buffer, 1, 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (c == 0)
            {
                sprintf(filename, "%03i.jpg", c);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                if (img != NULL)
                {
                    fclose(img);
                    sprintf(filename, "%03i.jpg", c);
                    img = fopen(filename, "w");
                    fwrite(buffer, 1, 512, img);
                }
            }
            c++;
        }
        else
        {
            if (img != NULL)
            {
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    fclose(img);
    fclose(card);
}
