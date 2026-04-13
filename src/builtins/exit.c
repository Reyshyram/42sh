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
