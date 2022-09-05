// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef int16_t byte_2;

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

    // TODO: Copy header from input file to output file

    //Create an array of bytes to store the data from the WAV file header
    uint8_t header[44];

    fread(header, sizeof(uint8_t), 44, input);//read 44 bytes from input file
    fwrite(header, sizeof(uint8_t), 44, output);//write 44 bytes into output file

    // TODO: Read samples from input file and write updated data to output file
    byte_2 buffer;

    while (fread(&buffer, sizeof(byte_2), 1, input))
    {
        buffer *= factor;
        fwrite(&buffer, sizeof(byte_2), 1, output);
    }
    //loop through input file until you get to the end
    //read into memory each 2 bype, update volume, write updated sample to output file
    // Close files
    fclose(input);
    fclose(output);
}
