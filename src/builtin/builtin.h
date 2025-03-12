#pragma once

int num_builtin();
int cd(char **args);
int help(char **args);
int osh_exit(char **args);

extern char *builtin_list[]; 
extern int (*builtin_func[]) (char **);