/*
** EPITECH PROJECT, 2026
** builtins.c
** File description:
** The builtins builtin, which shows the builtins
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"

#include "builtins.h"
#include "shell.h"

int builtin_builtins([[maybe_unused]] shell_t *shell, size_t argc,
    [[maybe_unused]] char **argv)
{
    if (argc != 1) {
        my_puterr("builtins: Too many arguments.\n");
        return ERROR;
    }
    for (size_t i = 0; BUILTINS[i].name; i++)
        my_printf("%s\t", BUILTINS[i].name);
    my_putchar('\n');
    return SUCCESS;
}
