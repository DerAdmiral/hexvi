#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//Configure default values and then (re)compile:
#define DEFAULT_LINELENGTH 10;
#define DEFAULT_AMOUNTTOREAD 255;

struct _line {
    char* linecontent;
};
typedef struct _line line;

int linelength = DEFAULT_LINELENGTH;
int amounttoread = DEFAULT_AMOUNTTOREAD;

int read_counter = 0, lastreadbytes;
char *line_iterator;

FILE *sourcefile = NULL;
char *sourcefilename = NULL;
FILE *outputfile = NULL;
char *outputfilename = NULL;

line l;

int writeToOutputFile(char *line_iterator);
void initOutputFile();

int main(int argc, char *argv[]){
    int opt, errorinput = 110; //110 = ascii: 'n' 
    char currentchar;
    while((opt = getopt(argc, argv, "f:o:n:l:")) != -1){
        switch(opt) {
            case 'f':{
                if(!(sourcefile = fopen(optarg, "r"))){
                    fprintf(stderr, "[!] Couldn't open sourcefile: %s\n", optarg);
                    exit(EXIT_FAILURE);
                }
                sourcefilename = strdup(optarg);
                break;
            }
            case 'o':{
                if(!(outputfile = fopen(optarg, "w"))){
                    fprintf(stderr, "<!> Couldn't open output file: %s\nexit[Y/n]", optarg);
                    errorinput = fgetc(stdin);
                    if(! (errorinput == 110 || errorinput == 78)){
                        fflush(stdin);
                        fprintf(stderr, "exitting...");
                        exit(EXIT_FAILURE);
                    }
                    fflush(stdin);
                }
                outputfilename = strdup(optarg);
                break;
            }
            case 'n':{
                amounttoread = atoi(optarg);
                break;
            }
            case 'l':{
                linelength = atoi(optarg);
                break;
            }
            default:{
                break;
            }
        }
    }
    if(!(l.linecontent = (char *) calloc(linelength, sizeof(char)))) { //Request memory to store the bytes read from the file to store in 
        printf("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    //printf("Passed argmunets:\nSourcefile: %p\nOutputfile %p\nMemory for line content: %p\nAmount of bytes to read %d\nLinelengtg %d\n", sourcefile, outputfile, l.linecontent, amounttoread, linelength);
    if(!sourcefile) {
        fprintf(stderr, "Please privide a source file with '-f <path to sourcefile>'");
        exit(EXIT_FAILURE);
    }
    if(outputfile) initOutputFile(amounttoread);
    do{
        line_iterator = l.linecontent; // setting line_iterator to the address of linecontent, thus there is always a pointer pointing to the beginning of the memory block
        for(int i = 0; i < linelength; i++) {
            fread(++line_iterator, 1, 1, sourcefile);
            ++read_counter;
            printf("%04hhx ", *line_iterator);
            if(*line_iterator == EOF || read_counter >= amounttoread) {
                lastreadbytes = i; // count the amount of bytes, which have to be printed as chars 
                break;
            }
            lastreadbytes = i;
        }
        line_iterator = l.linecontent;
        printf("    ");
        for (int i = 0; i <= lastreadbytes; i++) {
            currentchar = *(++line_iterator);
            if(currentchar == 10){
                printf("\\n"); //prevent newline characters from being printed, thereby the output format doesn't get messed up
            }else { printf("%c", isgraph(currentchar) ? currentchar : '.');}
        }
        line_iterator = l.linecontent;
        writeToOutputFile(line_iterator);
        memset(l.linecontent, 0, linelength);
        printf("\n");
    }while(read_counter < amounttoread);

    printf("\n");

    free(l.linecontent);
    free(sourcefilename);
    free(outputfilename);
    fclose(sourcefile);
    fclose(outputfile);

    return 0;
}

int writeToOutputFile(char *line_iterator) {
    char currentchar, *temp_line_iterator;
    temp_line_iterator = line_iterator;
    for(int i = 0; i <= lastreadbytes; i++) {
        fprintf(outputfile, "%04hhx ", *(++temp_line_iterator));
    }
    fprintf(outputfile, "   ");
    temp_line_iterator = line_iterator;
    for(int i = 0; i <= lastreadbytes; i++) {
        currentchar = *(++temp_line_iterator);
        if(currentchar == 10){
            fprintf(outputfile, "\\n");
        }else { fprintf(outputfile, "%c", isgraph(currentchar) ? currentchar : '.');}
    }
    fprintf(outputfile, "\n");
    return 0;
}

void initOutputFile(int bytestoread){
    printf("Init file\n");
    time_t time_of_beginning = time(NULL);
    fprintf(outputfile, "%s\n\nSourcefile: %s\nOutputfile: %s[%d]\nTime: %s\n", __FILE__, sourcefilename, outputfilename, bytestoread, ctime(&time_of_beginning));
}