#include <stdio.h>

int main(int argc, char *argv[])
{
    //DECLARATIONS
    char *cardfile = argv[1]; //FILENAME

    //ENSURE PROPER USAGE - ONE ARGUMENT ONLY!
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover cardfile\n");
        return 1;
    }

    //OPEN INPUT FILE
    FILE *inptr = fopen(cardfile, "r");//TESTING: BASED ON RECOVER HINTS
    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cardfile);
        return 2;
    }
    //DECLARATIONS FOR PIC DISCOVERY
    int file_prefix = 000; //COUNTER FOR JPEG NAMES
    int size = 512;
    unsigned char buffer[512];
    int jpegfound = 0; //or false
    FILE* image = NULL;

    //Check to see if block has JPEG header
    while (fread(buffer, size, 1, inptr) == 1)
    {
        if(//DOES THE CURRENT DATA HAVE JPEG HEADER?
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {   //IF HEADER IS FOUND - WRITE TO JPG FILE.
                if(jpegfound==1)
                {
                    //found a pic
                    fclose(image);
                }
                else
                {
                    //jpeg found and we can write
                    jpegfound = 1;//or true
                }

                char filename[8];
                sprintf(filename, "%03d.jpg", file_prefix);
                image = fopen(filename, "w");
                file_prefix++;
            }
        if (jpegfound == 1)
        {
            //WRITE 512 BYTES TO FILE AS WE FIND HEADERS
            fwrite(&buffer, size, 1, image);
        }
    }

    //Success!

    fclose(inptr);
    fclose(image);
    return 0;
}