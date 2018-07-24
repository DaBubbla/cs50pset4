#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];


    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfn;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfn = bf;       // bfn for new

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bin;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bin = bi;       // bin for new

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    // |||||DEFINITIONS OF NEW AND OLD STRUCTS lines 61 to 74|||||||

    // define new width and height
    bin.biWidth = bi.biWidth * n;
    bin.biHeight = bi.biHeight * n;

    // define old and new padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int npadding = (4 - (bin.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // define old and new bfSize and biSizeImage
    bi.biSizeImage = ((bi.biWidth * sizeof(RGBTRIPLE)) + padding) * abs(bi.biHeight);  // biHeight must be absolute value
    bf.bfSize = bi.biSizeImage + 54;

    bin.biSizeImage = ((bin.biWidth * sizeof(RGBTRIPLE)) + npadding) * abs(bin.biHeight); // biHeight must be absolute value
    bfn.bfSize = bin.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfn, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bin, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // read scanlines n times
        for (int j = 0; j < n; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // write RGB triple to outfile n times
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // write padding to outfile
            for (int m = 0; m < npadding; m++)
            {
                fputc(0x00, outptr);
            }
            // send cursor back a total of bi.biWidth*pixels to the left
            if (j < n - 1)
            {
                fseek(inptr, (-bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}