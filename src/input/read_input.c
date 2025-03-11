#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/defines.h"

#include "read_input.h"

char *read_input(void) {
    char *current_line = NULL;
    ssize_t buffer_size = 0;

    // Allocate a buffer to read in the current line from stdin
    if (getline(&current_line, &buffer_size, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readinput");
            exit(EXIT_FAILURE);
        }
    }

    return current_line;
}