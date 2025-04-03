#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../util/defines.h"

#include "builtin.h"

char *builtin_list[] = {
    "cd",
    "echo",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &cd,
    &echo,
    &help,
    &osh_exit
};

int num_builtin() {
    return sizeof(builtin_list) / sizeof(char *);
}

int cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "osh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("osh");
        }
    }
    return 1;
}

int echo(char **args) {
    int newline = 1;
    int idx = 1;

    if (args[1] && strcmp(args[1], "-n") == 0) {
        newline = 0;
        idx++;
    }

    for (; args[idx] != NULL; ++idx) {
        printf("%s", args[idx]);
        if (args[idx + 1] != NULL) {
            printf(" ");
        }
    }

    if (newline) {
        printf("\n");
    }

    return 1;
}

int osh_exit(char **args) {
    return 0;
}

int help(char **args) {
    printf("osh: The Open Shell\n");
    printf("The following commands are currently supported:\n");

    for (int i = 0; i < num_builtin(); ++i) {
        printf("  %s\n", builtin_list[i]);
    }

    return 1;
}
