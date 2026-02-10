/*
** EPITECH PROJECT, 2025
** my/shell.h
** File description:
** Main shell things
*/

#ifndef SHELL_H
// clang-format off
    #define SHELL_H
// clang-format on

typedef struct shell {
    char **env;
    int last_status;
    bool interactive;
} shell_t;

int shell_run(char **env);
char *read_input(bool interactive);

#endif /* SHELL_H */
