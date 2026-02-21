/*
** EPITECH PROJECT, 2026
** exit.c
** File description:
** Exit builtin
*/

#include <stddef.h>

#include "my/io.h"
#include "my/misc.h"
#include "my/numbers.h"
#include "my/strings.h"

#include "shell.h"

int builtin_exit(shell_t *shell, size_t argc, char **argv)
{
    if (argc > 2) {
        my_puterr("exit: Expression Syntax.\n");
        return ERROR;
    }
    if (argc == 1) {
        shell->should_exit = true;
        shell->should_exit_status = 0;
        return SUCCESS;
    }
    if (!my_str_isnum(argv[1])) {
        if (my_isnumber(argv[1][0]))
            my_puterr("exit: Badly formed number.\n");
        else
            my_puterr("exit: Expression Syntax.\n");
        return ERROR;
    }
    shell->should_exit = true;
    shell->should_exit_status = (int) my_getnbr(argv[1]);
    return SUCCESS;
}
