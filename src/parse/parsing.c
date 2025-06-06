#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/defines.h"

#include "parsing.h"

char **parse_input(char *line) {
    int buffer_size = MAX_TOKEN_BUFFER;
    int idx = 0;
    char **tokens = malloc(sizeof(char*) * buffer_size);
    char *current_token;
    char **prev_buffer;

    if (!tokens) {
        fprintf(stderr, "osh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    current_token = strtok(line, TOKEN_DELIM); // Initial tokenizing

    // Iterate through the current line, adding each token to the array
    while (current_token != NULL) {
        tokens[idx] = current_token;
        idx++;

        // Reallocate the token buffer if necessary
        if (idx >= buffer_size) {
            buffer_size += MAX_TOKEN_BUFFER;
            prev_buffer = tokens;
            tokens = realloc(tokens, (sizeof(char*) * buffer_size));

            if (!tokens) {
                free(prev_buffer); 
                fprintf(stderr, "osh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        current_token = strtok(NULL, TOKEN_DELIM); // Proceed through the current line
    }
    
    // Add a null character to terminate the token array
    tokens[idx] = NULL;
    return tokens;
}