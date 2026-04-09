/*
** EPITECH PROJECT, 2026
** set.c
** File description:
** set builtin
*/

#include <string.h>

#include "my/io.h"
#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

static int compare_variable(variable_t *a, variable_t *b)
{
    return my_strcmp(a->key, b->key);
}

static void print_variables(shell_t *shell)
{
    variable_t *data = nullptr;

    shell->variables =
        my_sort_list(shell->variables, (void *) compare_variable);
    for (linked_list_t *node = shell->variables; node; node = node->next) {
        data = node->data;
        my_printf("%s\t%s\n", data->key, data->value);
    }
}

static bool is_valid_name(char *str)
{
    if (!str || !(my_isupper(str[0]) || my_islower(str[0]) || str[0] == '_')) {
        my_puterr("set: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 1; str[i]; i++) {
        if (!(my_isupper(str[i]) || my_islower(str[i]) || my_isnumber(str[i])
                || str[i] == '_')) {
            my_puterr(
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
            my_puterr("setenv: Couldn't allocate memory for variable.\n");
            return false;
        }
        return true;
    }
    if (!set_variable(&shell->variables, key, value)) {
        my_puterr("setenv: Couldn't allocate memory for variable.\n");
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
            my_puterr("set: Variable name must begin with a letter.\n");
            return ERROR;
        }
        if (!set_single_var(shell, argv[i]))
            return ERROR;
    }
    return SUCCESS;
}
