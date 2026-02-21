/*
** EPITECH PROJECT, 2025
** shell.h
** File description:
** Main shell things
*/

#ifndef SHELL_H
// clang-format off
    #define SHELL_H

    #include "my/list.h"

    #define PROGRAM_NAME "mysh"
// clang-format on

typedef struct shell {
    linked_list_t *env;
    linked_list_t *variables;
    int last_status;
    int should_exit_status;
    bool interactive;
    bool should_exit;
} shell_t;

typedef struct {
    char *key;
    char *value;
} variable_t;

void free_variable(variable_t *variable);
char *get_variable_value(linked_list_t *variables, char *key);
variable_t *get_variable(linked_list_t *variables, char *key);
bool set_variable(linked_list_t **variables, char *key, char *value);

int shell_run(char **env);
char *read_input(linked_list_t *variables, bool interactive, int last_status);

#endif /* SHELL_H */
