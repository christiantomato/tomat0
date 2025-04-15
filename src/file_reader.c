#include "include/file_reader.h"
#include <stdio.h>
#include <stdlib.h>

//implement the file read method
char* read_file(const char* filename) {
    //attempts to read from the file
    FILE* tomat0_file = fopen(filename, "r");
    if(tomat0_file == NULL) {
        //error opening file
        printf("error opening file\n");
    }

    //determine file size
    //go to end
    fseek(tomat0_file, 0, SEEK_END);
    //get pointer location
    long file_size = ftell(tomat0_file);
    //put pointer in tomat0 file back to beginning
    rewind(tomat0_file);

    //allocate the appropriate memory for the file contents (+1 since we have to add the null termination for string)
    char* file_contents = malloc(file_size + 1);
    //read in everything to file_contents
    fread(file_contents, sizeof(char), file_size, tomat0_file);
    //null terminate the string
    file_contents[file_size] = '\0';

    //close the file and return the contents
    fclose(tomat0_file);
    return file_contents;
}
