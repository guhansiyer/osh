#pragma once

int launch(char **args);
int check_builtin(char **args);
int execute(char **args);
int execute_pipe(char **args, int idx);
int redirect(char **args, int in_idx, int out_idx);
void cleanup_redirect(int s_stdin, int s_stdout);