#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "../builtin/builtin.h"
#include "../exec/exec.h"
#include "../input/read_input.h"
// #include "../history/history.h"
#include "../parse/parsing.h"
#include "../util/defines.h"

void osh_main(void) {
    char *line;
    char **args;
    int status;

    read_history(NULL);

    do {
        printf("osh $ ");
        line = read_input();
        args = parse_input(line);
        status = execute(args);

        free(line);
        free(args);
    } while(status);

    write_history(NULL);
}

int main(int argc, char **argv) {

    osh_main();

    return EXIT_SUCCESS;
}