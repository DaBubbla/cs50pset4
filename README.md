# cs50pset4
A respository for CS50's pset 4: Whodunit, resize, recover


This repo is my solution for CS50's problem set 4.

/*
In Whodunit I am given a bitmap image that contains 'evidence' that has been 'altered'
my solution was to iterate through the pixels in the image and change everything to red.
The hint I received explained the red piece of plastic we had as kids to decode secret
messages. So, I made a piece of red plastic!

In resize, I was given similar images from whodunit. The object of this was to write a
program that accepts command line arguments including: a number to resize the image by,
the infile or image to be resized, and the outfile. 
The program written takes the pixels from the infile's bitmap and duplicates them 
'n' times to account for horizontal scaling. For height I stored this in an array to be 
copied 'n' times to address the height. 
So, if the example is :  XO
                         OX
      IF WE SET 'NTH' TO 4
                        
The output is: X X X X O O O O
               X X X X O O O O
               X X X X O O O O
               X X X X O O O O
               O O O O X X X X
               O O O O X X X X
               O O O O X X X X
               O O O O X X X X
               O O O O X X X X
               
Recover in progress.
*/
