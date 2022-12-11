# About hexvi

hexvi is a simple heviewer to inspect files 
Compatibility:  
-Linux  
-maybe macos (haven't had the opportunity to test it)


## Usage

There are four options:  
 -f exepects a path to a file to read bytes from  
 -o the output is copied to this file  
 -n read n bytes from f  
 -l set the amount of characters to print in each line  
You can set your own default values for linelength and the amount of bytes to read  
For the linelength go to line 9 (#define DEFAULT_LINELENGTH) and change the value  
In order to change the default amount of bytes to read, go to line 10 (#define DEFAULT_AMOUNTTOREAD) and change the value

## Documentation

hexvi iterates over the given parameter using optarg.
It opens the source file and the outputfile (if provided) using fopen(optarg, 'r'), where optarg is the filename.  
After that the process uses calloc(linelength, sizeof(char)) to allocate sufficient memory to store the linecontent in  
Afterward some extra informations are written to the output file (if there is one)  
Now the process uses the counter variable read_counter to keep track of the amount bytes which have been read.  
The variable lastreadbytes makes sure that the exact amount of bytes which have been read are printed as characters to the terminal.  
Between the two for-loops the pointer line_iterator is reseted to the beginning of the memory block.  
Furthermore newline characters are supress to keep a pretty output format.  
The writeToOutPutFile() function works just like the iterating process in the main function, it only replaces printf()  
with fprintf(outputfile, "%c", *(++temp_linecontent)), thus the output on the terminal is copied to the outputfile.  
At the end all the memory occupied the process is freed (free()) and the files are close(fclose()).
