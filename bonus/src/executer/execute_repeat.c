/*
** EPITECH PROJECT, 2026
** execute_repeat.c
** File description:
** Repeat a command multiple times
*/

#include "ast.h"
#include "executer.h"
#include "shell.h"

// Needs to say it's not a subprocess, or it will
// not execute the commands in the current shell
int execute_repeat(shell_t *shell, ast_node_t *ast)
{
    int status = 0;
    bool prev_is_subprocess = shell->is_subprocess;

    shell->is_subprocess = false;
    for (int i = 0; i < ast->data.repeat.count; i++)
        status = execute_ast(shell, ast->data.repeat.node);
    shell->is_subprocess = prev_is_subprocess;
    return status;
}
