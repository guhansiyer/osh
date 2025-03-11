#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "./utils/defines.h"

#include "exec.h"

int launch(char **args) {
    pid_t pid, w_pid;
    int status;

    // Create child process
    pid = fork();

    // C
    if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("fork failure");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failure");
    } else {
        do {
            w_pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}