/*
** EPITECH PROJECT, 2026
** unsetenv.c
** File description:
** unsetenv builtin
*/

#include <stdio.h>

#include "my/misc.h"

#include "shell.h"

/*************************************
* The builtin_unsetenv function handles the unsetenv builtin for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, either an error or a success
*************************************/
int builtin_unsetenv(shell_t *shell, size_t argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "unsetenv: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++)
        unset_variable(&shell->env, argv[i]);
    return SUCCESS;
}
