/*
** EPITECH PROJECT, 2026
** setenv.c
** File description:
** setenv builtin
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"
#include "my/strings.h"

#include "builtins.h"
#include "shell.h"

static bool is_valid_name(char *str)
{
    if (!(my_isupper(str[0]) || my_islower(str[0]) || str[0] == '_')) {
        my_puterr("setenv: Variable name must begin with a letter.\n");
        return false;
    }
    for (size_t i = 1; str[i]; i++) {
        if (!(my_isupper(str[i]) || my_islower(str[i]) || my_isnumber(str[i])
                || str[i] == '_')) {
            my_puterr(
                "setenv: Variable name must contain alphanumeric "
                "characters.\n");
            return false;
        }
    }
    return true;
}

int builtin_setenv(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1)
        return builtin_env(shell, argc, argv);
    if (argc > 3) {
        my_puterr("setenv: Too many arguments.\n");
        return ERROR;
    }
    if (!is_valid_name(argv[1]))
        return ERROR;
    if (argc == 3) {
        if (!set_variable(&shell->env, argv[1], argv[2])) {
            my_puterr("setenv: Couldn't allocate memory for variable.\n");
            return ERROR;
        }
        return SUCCESS;
    }
    if (!set_variable(&shell->env, argv[1], "")) {
        my_puterr("setenv: Couldn't allocate memory for variable.\n");
        return ERROR;
    }
    return SUCCESS;
}
