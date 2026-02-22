/*
** EPITECH PROJECT, 2026
** execute_ast.c
** File description:
** Execute the command following the ast
*/

#include "my/io.h"
#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

int execute_ast(shell_t *shell, ast_node_t *ast)
{
    if (!ast)
        return SUCCESS;
    if (ast->type == AST_CMD)
        return execute_cmd(shell, ast);
    if (ast->type == AST_SEQUENCE)
        return execute_sequence(shell, ast);
    if (ast->type == AST_LOGICAL_AND)
        return execute_logical_and(shell, ast);
    if (ast->type == AST_LOGICAL_OR)
        return execute_logical_or(shell, ast);
    my_puterr("Unknown AST node encountered in the executor.\n");
    return ERROR;
}
