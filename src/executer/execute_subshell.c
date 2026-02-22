/*
** EPITECH PROJECT, 2026
** execute_subshell.c
** File description:
** Execute a subshell
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/io.h"
#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

int execute_subshell(shell_t *shell, ast_node_t *ast)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1) {
        my_dprintf(STDERR_FILENO, "fork: %s.\n", strerror(errno));
        return ERROR;
    }
    if (pid == 0) {
        status = execute_ast(shell, ast->data.subshell.node);
        exit(status);
    }
    return wait_for_subprocess(pid);
}
