#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "./exec/exec.h"

#include "./input/read_input.h"

#include "./parse/parsing.h"

#include "./util/defines.h"

void read_input(char *input) {
    printf("osh $ ");
    fgets(input, MAX_INPUT, stdin); // Read current input from input filestream.
    input[strcspn(input, '\n')] = 0; // Replace newline character.
}

void parse_input(char *input, char **args) {
    int idx = 0;
    char *token = strtok(input, ' ');
    
    // Processing the tokenized input.
    while ((token != NULL) && (idx < MAX_ARGS - 1)) {
        args[idx] = token;
        idx++;
        token = strtok(NULL, " ");
    }

    args[idx] = NULL; // Add null-terminating char to arg list.
}

void execute()

void osh_main(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("osh $ ");
        line = read_input();
        args = parse_input();
        status = execute();

        free(line);
        free(args);
    } while(status);
}

int main(int argc, char **argv) {

     
}