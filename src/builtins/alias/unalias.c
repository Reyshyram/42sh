/*
** EPITECH PROJECT, 2026
** unalias.c
** File description:
** The unalias builtin
*/

#include <stdio.h>
#include <string.h>

#include "builtins.h"
#include "my/misc.h"
#include "shell.h"

int builtin_unalias(shell_t *shell, size_t argc, char **argv)
{
    int status = SUCCESS;

    if (argc < 2) {
        fprintf(stderr, "unalias: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++) {
        if (!get_variable(shell->aliases, argv[i])) {
            fprintf(stderr, "unalias: %s: Not found.\n", argv[i]);
            status = ERROR;
            continue;
        }
        unset_variable(&shell->aliases, argv[i]);
    }
    return status;
}
