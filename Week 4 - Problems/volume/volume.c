// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Each byte of the header is a uint8_t value, so we can read them into an array of uint8_t
    uint8_t header[HEADER_SIZE];
    // We read HEADER_SIZE bytes from the input file into the header array.
    fread(header, HEADER_SIZE, 1, input);
    // We write the HEADER_SIZE bytes from the header to the output file without modification.
    fwrite(header, HEADER_SIZE, 1, output);

    // Temporary storage for a sound sample.
    uint16_t buffer;
    // fread returns the number of items read, which is 1 if successful, and 0 if it reaches the end of the file.
    // So we can use that to loop through the input file until we reach the end.
    while (fread(&buffer, sizeof(uint16_t), 1, input) != 0)
    {
        buffer = (factor * buffer);
        fwrite(&buffer, sizeof(uint16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}

