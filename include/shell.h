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
    bool interactive;
} shell_t;

int shell_run(char **env);
char *read_input(linked_list_t *env, bool interactive, int last_status);

#endif /* SHELL_H */
