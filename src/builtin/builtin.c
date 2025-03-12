#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./utils/defines.h"

#include "builtin.h"

char *builtin_list[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &cd,
    &help,
    &exit
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

int help(char **args) {
    printf("osh: The Open Shell\n");
    printf("The following commands are currently supported:\n")

    for (int i = 0; i < num_builtin(); ++i) {
        printf("%s\n", builtin_list[i]);
    }

    return 1;
}

int exit(char **args) {
    return 0;
}