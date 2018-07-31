#include <stdio.h>
//#include <cs50.h>

int main(int argc, char *argv[])
{
    //DECLARATIONS
    char *cardfile = argv[1]; //FILENAME
    int file_prefix = 000; //COUNTER FOR JPEG NAMES
    //DECLARE EOF...

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
    unsigned char buffer[512]; //UNSIGNED CHAR is critical to this step

    int size = 512;
    //fread cardfile and chop into 512 byte blocks
    fread(buffer, size, 1, inptr);
    //try oscar's while loop

    //Check to see if block has JPEG header

    for (int x = 0; x < sizeof(cardfile); x++)
    {
        if(//DOES THE CURRENT DATA HAVE JPEG HEADER?
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {   //IF HEADER IS FOUND - WRITE TO JPG FILE.
                file_prefix++;
                sprintf("recovered.jpg", "%u.jpg", file_prefix);
                //FILE *img_file = fopen("recovered.jpg", "w");
                //look up sprintf() documentation
            }
        else//IF HEADER IS NOT FOUND...
        {
            //continue through the cardfile...
        }

    }

    //OPEN CARD FILE
        //REPEAT UNTIL END OF CARD FILE
            //READ 512 BYTES INTO A BUFFER

            //START OF A NEW JPEG?
                //YES?
                //NO?
            //ALREAD FOUND A JPEG?
                //NO?
                //YES?
            //CLOSE REMAINING FILES

    //Success!
    return 0;
    fclose(inptr);
    //fclose(output??);
}