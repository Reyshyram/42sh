/*
** EPITECH PROJECT, 2026
** set.c
** File description:
** set builtin
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

static int compare_variable(variable_t *a, variable_t *b)
{
    return strcmp(a->key, b->key);
}

static void print_variables(shell_t *shell)
{
    variable_t *data = nullptr;

    shell->variables =
        my_sort_list(shell->variables, (void *) compare_variable);
    for (linked_list_t *node = shell->variables; node; node = node->next) {
        data = node->data;
        printf("%s\t%s\n", data->key, data->value);
    }
}

static bool is_valid_name(char *str)
{
    if (!str || !(isupper(str[0]) || islower(str[0]) || str[0] == '_')) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 1; str[i]; i++) {
        if (!(isupper(str[i]) || islower(str[i]) || my_isnumber(str[i])
                || str[i] == '_')) {
            fprintf(stderr,
                "set: Variable name must contain alphanumeric "
                "characters.\n");
            return false;
        }
    }
    return true;
}

static bool set_single_var(shell_t *shell, char *str)
{
    char *key = strtok(str, "=");
    char *value = strtok(nullptr, "=");

    if (!is_valid_name(key))
        return false;
    if (!value) {
        if (!set_variable(&shell->variables, key, "")) {
            fprintf(stderr,
                "setenv: Couldn't allocate memory for variable.\n");
            return false;
        }
        return true;
    }
    if (!set_variable(&shell->variables, key, value)) {
        fprintf(stderr, "setenv: Couldn't allocate memory for variable.\n");
        return false;
    }
    return true;
}

int builtin_set(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        print_variables(shell);
        return SUCCESS;
    }
    for (size_t i = 1; argv[i]; i++) {
        if (argv[i][0] == '=') {
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
            return ERROR;
        }
        if (!set_single_var(shell, argv[i]))
            return ERROR;
    }
    return SUCCESS;
}
