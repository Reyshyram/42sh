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

/*************************************
* The builtin_unalias function prints all the aliases for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the arg
*   @return -> an integer, an error or a success
*************************************/
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
