/*
** EPITECH PROJECT, 2026
** execute_repeat.c
** File description:
** Repeat a command multiple times
*/

#include "ast.h"
#include "executer.h"
#include "shell.h"

int execute_repeat(shell_t *shell, ast_node_t *ast)
{
    int status = 0;

    for (int i = 0; i < ast->data.repeat.count; i++)
        status = execute_ast(shell, ast->data.repeat.node);
    return status;
}
