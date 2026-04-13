/*
** EPITECH PROJECT, 2026
** builtins.c
** File description:
** The builtins builtin, which shows the builtins
*/

#include <stdio.h>

#include "builtins.h"
#include "my/misc.h"
#include "shell.h"

int builtin_builtins([[maybe_unused]] shell_t *shell, size_t argc,
    [[maybe_unused]] char **argv)
{
    if (argc != 1) {
        fprintf(stderr, "builtins: Too many arguments.\n");
        return ERROR;
    }
    for (size_t i = 0; BUILTINS[i].name; i++)
        printf("%s\t", BUILTINS[i].name);
    putchar('\n');
    return SUCCESS;
}
