/*
** EPITECH PROJECT, 2026
** exit.c
** File description:
** Exit builtin
*/

#include <stdio.h>
#include <stdlib.h>

#include "my/misc.h"
#include "my/strings.h"

#include "shell.h"

/*************************************
* The builtin_exit function handles the builtin exit for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, an error or a success
*************************************/
int builtin_exit(shell_t *shell, size_t argc, char **argv)
{
    if (argc > 2) {
        fprintf(stderr, "exit: Expression Syntax.\n");
        return ERROR;
    }
    if (argc == 1) {
        shell->should_exit = true;
        shell->last_status = 0;
        return SUCCESS;
    }
    if (!my_str_isnum(argv[1])) {
        if (my_isnumber(argv[1][0]))
            fprintf(stderr, "exit: Badly formed number.\n");
        else
            fprintf(stderr, "exit: Expression Syntax.\n");
        return ERROR;
    }
    shell->should_exit = true;
    shell->last_status = atoi(argv[1]);
    return shell->last_status;
}
