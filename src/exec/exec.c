#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../util/defines.h"
#include "../builtin/builtin.h"

#include "exec.h"

int launch(char **args) {
    pid_t pid, w_pid;
    int status;

    // Create child process
    pid = fork();

    // Check for for failures and wait for process to finish executing
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

int execute(char **args) {

    // Check for null argument (blank string)
    if (args[0] == NULL) {
        return 1;
    }

    // Check if the input args list has a command matching a builtin
    for (int i = 0; i < num_builtin(); ++i) {
        if (strcmp(args[0], builtin_list[i]) == 0) {
            return (*builtin_func[i])(args);
        } 
    }

    // Launch a process if no builtin was found
    return launch(args);
}