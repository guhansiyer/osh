#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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

int check_builtin(char **args) {
    for (int i = 0; i < num_builtin(); ++i) {
        if (strcmp(args[0], builtin_list[i]) == 0) {
            return (*builtin_func[i])(args);
        } 
    }
    return -1;
}

int execute_pipe(char **args, int idx) {
    args[idx] = NULL;
    char **left = args;
    char **right = &args[idx + 1];

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t left_chld = fork();

    if (left_chld == 0) {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (!check_builtin(left)) {
            launch(left);
        }

        exit(EXIT_FAILURE);
    }

    pid_t right_chld = fork();

    if (right_chld == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (!check_builtin(right)) {
            launch(right);
        }

        exit(EXIT_FAILURE);
    
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(left_chld, NULL, 0);
    waitpid(right_chld, NULL, 0);
}

int redirect(char **args, int in_idx, int out_idx) {
    char *in_file = NULL;
    char *out_file = NULL;

    if (out_idx != -1) {
        out_file = args[out_idx + 1];
        args[out_idx] = NULL;
        args[out_idx + 1] = NULL;
    } if (in_idx != -1) {
        in_file = args[in_idx + 1];
        args[in_idx] = NULL;
        args[in_idx + 1] = NULL;
    }

    if (in_file) {
        int fd = open(in_file, O_RDONLY);

        if (fd < 0) {
            perror("open for input");
            return -1;
        }

        dup2(fd, STDIN_FILENO);
        close(fd);
    } if (out_file) {
        int flags = O_WRONLY | O_CREAT | O_TRUNC;
        int fd = open(out_file, flags, 0644);
        
        if (fd < 0) {
            perror("open for output");
            return -1;
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    return 0;
}

void cleanup_redirect(int s_stdin, int s_stdout) {
    dup2(s_stdin, STDIN_FILENO);
    dup2(s_stdout, STDOUT_FILENO);
    close(s_stdin);
    close(s_stdout);
}

int execute(char **args) {

    // Check for null argument (blank string)
    if (args[0] == NULL) {
        return 1;
    }

    int pipe_idx = -1;
    int rdr_in = -1;
    int rdr_out = -1;

    // Check for pipes or redirection in args list
    for (int i = 0; args[i] != NULL; ++i) {
        if (strcmp(args[i], "|") == 0) {
            pipe_idx = i;
        } else if (strcmp(args[i], ">") == 0) {
            rdr_out = i;
        } else if (strcmp(args[i], "<") == 0) {
            rdr_in = i;
        }
    }

    // If the input pipes command, call appropriate function
    if (pipe_idx != -1) {
        return execute_pipe(args, pipe_idx);
    }

    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (rdr_in != -1 || rdr_out != -1) {
        if (redirect(args, rdr_in, rdr_out) != 0) {
            cleanup_redirect(saved_stdin, saved_stdout);
            return 1;
        }
    }

    // Check if the input args list has a command matching a builtin
    int res = check_builtin(args);

    if (res != -1) {
        cleanup_redirect(saved_stdin, saved_stdout);
        return res;
    }
    
    // Launch a process if no builtin was found
    res = launch(args);

    cleanup_redirect(saved_stdin, saved_stdout);

    return res;
}