/*
** EPITECH PROJECT, 2026
** execute_logical_and.c
** File description:
** Execute right command if left one didn't fail
*/

#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

int execute_logical_and(shell_t *shell, ast_node_t *ast)
{
    int status = execute_ast(shell, ast->data.binary.left);

    if (status != SUCCESS)
        return status;
    return execute_ast(shell, ast->data.binary.right);
}
