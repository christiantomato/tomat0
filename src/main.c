#include "include/all.h"
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    //lets read from the tomat0 file
    char* file_contents;
    FILE* tomat0_file; 
    tomat0_file = fopen("/Users/christiantamayo/VSCodeProjects/tomat0/examples/main.tmt", "r");
    if(tomat0_file == NULL) {
        //error
        printf("error opening file\n");
    }

    //determine file size

    //go to end
    fseek(tomat0_file, 0, SEEK_END);
    //get pointer location
    long file_size = ftell(tomat0_file);
    //put pointer in tomat0 file back to beginning
    rewind(tomat0_file);

    //allocate the appropriate memory for fileContents (+1 since we have to add the null termination for string)
    file_contents = malloc(file_size + 1);
    fread(file_contents, sizeof(char), file_size, tomat0_file);
    //null terminate the string
    file_contents[file_size] = '\0';

    //tokenize with lexer
    printf("%s", file_contents);
    lexer* my_lexer = init_lexer(file_contents);
    token* token = (void*)0;
    while((token = tokenize_next(my_lexer)) != NULL) {
        printf("Token type: %s, Token value: %s \n", token_type_str(token), token->value);
        //free the token as it is not needed anymore
        free(token);
    }

    fclose(tomat0_file);
    free(file_contents);
    free(my_lexer);
    return 0;
}