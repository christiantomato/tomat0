#include "include/file_reader.h"
#include <stdio.h>
#include <stdlib.h>

/*
Read File Function

reads all the contents from a file (in our case the .tmt file),
and builds a string pointer

const char* filename: the name of the file to be read

return: the string pointer containing the contents
*/

char* read_file(const char* filename) {
    //open the file in read mode
    FILE* tomat0_file = fopen(filename, "r");
    //check if opened correctly
    if(tomat0_file == NULL) {
        printf("error opening file\n");
    }
    
    //go to end of file with cursor
    fseek(tomat0_file, 0, SEEK_END);
    //determine the file size from cursor
    long file_size = ftell(tomat0_file);
    //put cursor in tomat0 file back to beginning
    rewind(tomat0_file);
    //allocate the appropriate memory for the file contents (+1 since we have to add the null termination for string)
    char* file_contents = malloc(file_size + 1);
    //read in everything to the allocated string
    fread(file_contents, sizeof(char), file_size, tomat0_file);
    //null terminate the string
    file_contents[file_size] = '\0';

    //close the file and return the contents
    fclose(tomat0_file);
    return file_contents;
}
