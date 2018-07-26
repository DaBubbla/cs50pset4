#include <stdio.h>
//#include <cs50.h>


int main(int argc, char *argv[])
{
    //ENSURE PROPER USAGE - ONE ARGUMENT ONLY!
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }
    //DECLARE FILENAME
    char *infile = argv[1];
    //char *outfile = argv[2]; in case outfile must be specified...

    //OPEN INPUT FILE
    FILE *inptr = fopen(infile, "r");
    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
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