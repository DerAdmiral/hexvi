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
