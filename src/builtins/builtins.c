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

/*************************************
* The builtin_builtins function handles the builtins for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the arg
*   @return -> an integer, an error or a success
*************************************/
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
