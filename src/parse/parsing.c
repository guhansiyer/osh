#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/defines.h"

#include "parsing.h"

char **parse_input(char *line) {
    int buffer_size = MAX_TOKEN_BUFFER;
    int idx = 0;
    char **tokens = malloc(sizeof(char) * MAX_TOKEN_BUFFER);
    char *current_token;

    if (!tokens) {
        fprintf(stderr, "osh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    current_token = strtok(line, TOKEN_DELIM); // Initial tokenizing

    // Iterate through the current line, adding each token to the array
    while (token != NULL) {
        tokens[idx] = token;
        idx++;

        // Reallocate the token buffer if necessary
        if (idx >= MAX_TOKEN_BUFFER) {
            buffer_size += MAX_TOKEN_BUFFER;
            tokens = realloc(tokens, (sizeof(char) * MAX_TOKEN_BUFFER));

            if (!tokens) {
                fprintf(stderr, "osh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        
        tokens = strtok(NULL, TOKEN_DELIM); // Proceed through the current line
    }
    
    // Add a null character to terminate the token array
    tokens[idx] = NULL;
    return tokens;
}