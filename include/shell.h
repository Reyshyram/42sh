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

    #define PROGRAM_NAME "42sh"
// clang-format on

typedef struct shell {
    linked_list_t *env;
    linked_list_t *variables;
    linked_list_t *aliases;
    int last_status;
    bool interactive;
    bool should_exit;
    bool is_out_redirected;
    bool is_in_redirected;
} shell_t;

typedef struct {
    char *key;
    char *value;
} variable_t;

void free_variable(variable_t *variable);
char *get_variable_value(linked_list_t *variables, char *key);
variable_t *get_variable(linked_list_t *variables, char *key);
bool set_variable(linked_list_t **variables, char *key, char *value);
void unset_variable(linked_list_t **variables, char *key);

int shell_run(char **env);
int handle_input(shell_t *shell, char *line);
char *read_input(linked_list_t *variables, bool interactive, int last_status);
void empty_stdin(void);

bool init_shell(shell_t *shell, char **env);
bool init_variables(shell_t *shell);
void handle_sigint(int signal);

#endif /* SHELL_H */
