# Questions

## What's `stdint.h`?

TODO:

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

TODO:

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

TODO

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

TODO

## What's the difference between `bfSize` and `biSize`?

TODO: biSize refers to the the size of the image or pixel itself.
        bfSize = biSize + 54 (or  bitmapfileheader 14  +  bitmapinfoheader 40)
        refers to the image plus the file and info headers.

## What does it mean if `biHeight` is negative?

TODO: "If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner...
indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS. 
Top-down DIBs cannot be compressed."

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

TODO

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

TODO

## Why is the third argument to `fread` always `1` in our code?

TODO

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

TODO

## What does `fseek` do?

TODO

## What is `SEEK_CUR`?

TODO
