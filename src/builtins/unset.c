/*
** EPITECH PROJECT, 2026
** unset.c
** File description:
** unset builtin
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"

#include "shell.h"

int builtin_unset(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        my_puterr("unset: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++)
        unset_variable(shell->variables, argv[i]);
    return SUCCESS;
}
