// Resizes an image according to Command-line
// to the n'th value.

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize 'n' infile outfile\n");
        return 1;
    }

    // remember filenames
    int nth = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    //Verify 'n' is a num between 1-100
    if(nth < 1 || nth >= 100)
    {
        fprintf(stderr, "Usage: n should be an int between 1 and 100\n");
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    //*******************************************************************

        //store infile's height, width, and padding
        int width_in = bi.biWidth;
        int height_in = abs(bi.biHeight);
        int padding_in = (4 - (width_in * sizeof(RGBTRIPLE)) % 4) % 4;

        //change header props to match scale
        bi.biWidth *= nth;
        bi.biHeight *= nth;
        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        bi.biSizeImage = ((3 * bi.biWidth) + padding) * height_in;// What the fuck is this 3??! -- 3 refers to the size of the bytes
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER)+ sizeof(BITMAPINFOHEADER);

    //*******************************************************************

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < height_in; i++)
    {
        //make an array to store the arr being written
        RGBTRIPLE arr[bi.biWidth];

            // iterate over pixels in scanline
            for (int j = 0; j < width_in; j++)
            {

                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile*****with resized pixels
                for(int x = 0; x < nth; x++)
                {
                   arr[x + (nth * j)] = triple;
                }
            }
                for (int j = 0; j < nth; j++)
                {
                    fwrite(arr, sizeof(arr), 1, outptr);
                    for (int k = 0; k < padding_in; k++)
                    {
                        fputc(0x00, outptr);
                    }
                }


            // skip over padding, if any
            fseek(inptr, padding_in, SEEK_CUR);
}

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
