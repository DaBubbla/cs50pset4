#include <stdio.h>
//#include <cs50.h>

int main(int argc, char *argv[])
{
    //DECLARATIONS
    char *cardfile = argv[1]; //FILENAME
    int file_prefix = 000; //COUNTER FOR JPEG NAMES

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

    //DECLARE BUFFER TO AID IN JPEG IDENTIFICATION
    int size = 512;
    unsigned char buffer[512];

    //RESERVE MEMORY FOR IMAGES
    FILE *image = NULL;

    //SET CONDITION TO FALSE / 0 - CURRENTLY NO HEADER IS FOUND
    int header_found = 0;

    //VERIFY THERE IS A JPEG HEADER
    while(fread(buffer, size, 1, inptr) == 1)// WHILE READING...
    {
        if(//SEARCH FOR JPEG HEADER...
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {   //IF HEADER IS FOUND - FORGET PREVIOUS DATA.
                if(header_found == 1)
                {
                    fclose(image);
                }
                else
                {
                    //ELSE SET HEADER TO TRUE
                    //SO WE CAN WRITE
                    header_found = 1;
                }

            }

        if (header_found == 1)
        {
            //CREATE A VAR TO NAME + WRITE IMAGE
            //INCREMENT FILEPREFIX FOR JPEG NAME
            char filename [10];
            sprintf(filename, "%03i.jpg", file_prefix);
            image = fopen(filename, "w");
            file_prefix++;
            //AND WRITE IT TO IMAGE
            fwrite(&buffer, size, 1, image);
        }
    }
    //SUCCESS - NOW CLOSE IT ALL UP
    fclose(inptr);
    fclose(image);
    return 0;
}