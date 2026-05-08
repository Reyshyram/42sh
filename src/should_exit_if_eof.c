/*
** EPITECH PROJECT, 2026
** should_exit_if_eof.c
** File description:
** Should exit the shell if encounter eof
*/

#include <stdio.h>
#include <stdlib.h>

#include "my/strings.h"

#include "shell.h"

/*************************************
* The should_exit_if_eof function handles if there
* is an eof and exits for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @return -> a boolean, either true or false
*************************************/
bool should_exit_if_eof(shell_t *shell)
{
    char *ignoreeof = nullptr;
    bool should_exit = true;

    if (!shell->interactive || !feof(stdin))
        return true;
    ignoreeof = get_variable_value(shell->variables, "ignoreeof");
    if (!ignoreeof)
        return true;
    shell->eof_count++;
    if (!ignoreeof[0] || !my_str_isnum(ignoreeof) || atoi(ignoreeof) == 0)
        should_exit = shell->eof_count >= MAX_EOF_DEFAULT;
    else
        should_exit = shell->eof_count >= atoi(ignoreeof);
    if (!should_exit) {
        clearerr(stdin);
        puts("^D\nUse \"exit\" to leave 42sh.");
    }
    return should_exit;
}
