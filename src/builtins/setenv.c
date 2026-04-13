/*
** EPITECH PROJECT, 2026
** setenv.c
** File description:
** setenv builtin
*/

#include <ctype.h>
#include <stdio.h>

#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

static bool is_valid_name(char *str)
{
    if (!(isupper(str[0]) || islower(str[0]) || str[0] == '_')) {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 1; str[i]; i++) {
        if (!(isupper(str[i]) || islower(str[i]) || my_isnumber(str[i])
                || str[i] == '_' || str[i] == '.')) {
            fprintf(stderr,
                "setenv: Variable name must contain alphanumeric "
                "characters.\n");
            return false;
        }
    }
    return true;
}

static int set_empty_variable(shell_t *shell, char *key)
{
    if (!set_variable(&shell->env, key, "")) {
        fprintf(stderr, "setenv: Couldn't allocate memory for variable.\n");
        return ERROR;
    }
    return SUCCESS;
}

int builtin_setenv(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1)
        return builtin_env(shell, argc, argv);
    if (argc > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return ERROR;
    }
    if (!is_valid_name(argv[1]))
        return ERROR;
    if (argc == 3) {
        if (!set_variable(&shell->env, argv[1], argv[2])) {
            fprintf(stderr,
                "setenv: Couldn't allocate memory for variable.\n");
            return ERROR;
        }
        return SUCCESS;
    }
    return set_empty_variable(shell, argv[1]);
}
