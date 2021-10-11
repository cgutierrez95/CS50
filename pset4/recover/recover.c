#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Check if just two arguments are passed.
    if (argc != 2)
    {
        printf("Usage ./recovery image");
        return 1;
    }
    
    //Check if the file can be opened.
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }
    
    BYTE buffer[512];
    
    int counter = 0;
    
    FILE *img_pointer = NULL;
    
    char filename[8];
    
    while (fread(&buffer, 512, 1, file) == 1)
    {
        //Check the header.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //Close the image
            if (!(counter == 0))
            {
                fclose(img_pointer);
            }
            
            //Create image file
            sprintf(filename, "%03i.jpg", counter);
            img_pointer = fopen(filename, "w");
            counter++;
        }
        
        //Save the data to the image file.
        if (!(counter == 0))
        {
            fwrite(&buffer, 512, 1, img_pointer);
        }
    }

    fclose(file);
    fclose(img_pointer);
}