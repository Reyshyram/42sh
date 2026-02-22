/*
** EPITECH PROJECT, 2026
** unsetenv.c
** File description:
** unsetenv builtin
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"

#include "shell.h"

int builtin_unsetenv(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        my_puterr("unsetenv: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++)
        unset_variable(shell->env, argv[i]);
    return SUCCESS;
}
