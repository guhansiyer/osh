#pragma once

int cd(char **args);
int echo(char **args);
int help(char **args);
int num_builtin();
int osh_exit(char **args);
int sinfo(char **args);

extern char *builtin_list[]; 
extern int (*builtin_func[]) (char **);