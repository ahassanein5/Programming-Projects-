Author Amr Hassanein

The objective of the project was to implement the lzw algorithm. In the first part, I took the demoIO function that was given to us and separated it into a write to file function and a read from file function.
The program takes 3 parameters, the execution file, a 'c' or 'e' character depending on whether you would like to either c - compress or e - expand, and finally the filename of the file you would like to either compress or decompress. 
When the program is started, it will either compress the given file of characters and write the compressed characters to the "example.lzw" file. 
To decompress you would run lzw435.exe e example.lzw to expand the file. The expanded output will be placed in the decompress.txt file. 

For the second part of the project, the objective was to compress a file even further by starting with 9 bit binary code and increasing up to 16 bit binary strings to save the characters. 
The file I/O is the same as the first part of the project which was described about.
To run this program you would enter lzw435M.exe c || e (depending once again whether you want to compress or expand) filename
the filename when decompressing will be the example.lzw file. this does not change. It will once again output your characters to the decompress.txt file. 