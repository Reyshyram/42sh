/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** builtin_time
*/

#include "ast.h"
#include "executer.h"
#include "my/misc.h"
#include "shell.h"
#include <stdio.h>
#include <sys/time.h>

/*************************************
* The builtin_time function handles the time builtin for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> size_t argc, the length of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, either an error or a success
*************************************/
int builtin_time(shell_t *shell, size_t argc, char **argv)
{
    ast_node_t ast_cmd = {0};
    struct timeval start;
    struct timeval end;
    int status = SUCCESS;
    double ms = 0;
    double s = 0;

    gettimeofday(&start, nullptr);
    if (argc > 1) {
        ast_cmd.type = AST_CMD;
        ast_cmd.data.cmd.argc = argc - 1;
        ast_cmd.data.cmd.argv = argv + 1;
        status = execute_cmd(shell, &ast_cmd);
    }
    gettimeofday(&end, nullptr);
    ms = (double) (end.tv_usec - start.tv_usec) / (double) 1'000'000;
    s = (double) (end.tv_sec - start.tv_sec);
    printf("Time taken: %.4fs\n", ms + s);
    return status;
}
