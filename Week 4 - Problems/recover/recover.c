#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    char name[8];
    uint8_t buffer[512];
    int image_count = 0;
    FILE *output = NULL;

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output != NULL)
            {
                fclose(output);
            }

            sprintf(name, "%03d.jpg", image_count);
            output = fopen(name, "w");
            image_count++;
        }

        if (output != NULL)
        {
            fwrite(buffer, 1, 512, output);
        }
    }
    fclose(output);
    fclose(card);
    return 0;
}
