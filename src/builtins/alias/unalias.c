/*
** EPITECH PROJECT, 2026
** unalias.c
** File description:
** The unalias builtin
*/

#include <stdio.h>

#include "my/misc.h"

#include "builtins.h"
#include "shell.h"

int builtin_unalias(shell_t *shell, size_t argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++)
        unset_variable(&shell->aliases, argv[i]);
    return SUCCESS;
}
