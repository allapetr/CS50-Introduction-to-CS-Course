#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check usage
    if (argc != 2)
    {
        return 1;
    }

    //Open file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    //Read first three bytes
    BYTE bytes[512];

    //Create new empty file
    char file_name[8];

    FILE *img = NULL;
    int fn = 0;
    while (fread(bytes, sizeof(BYTE), 512, file))
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            sprintf(file_name, "%03i.jpg", fn);//Create string of format ###.jpg
            if (img)
            {
                fclose(img);
            }

            img = fopen(file_name, "w");
            fn++;
            fwrite(bytes, sizeof(BYTE), 512, img);
        }
        else
        {
            if (img != NULL)
            {
                fwrite(bytes, sizeof(BYTE), 512, img);
            }

        }
    }

    //Close file
    fclose(img);
    fclose(file);

}
