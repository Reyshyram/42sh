/*
** EPITECH PROJECT, 2026
** execute_sequence.c
** File description:
** Execute a sequence of commands
*/

#include "ast.h"
#include "executer.h"
#include "shell.h"

int execute_sequence(shell_t *shell, ast_node_t *ast)
{
    execute_ast(shell, ast->data.binary.left);
    return execute_ast(shell, ast->data.binary.right);
}
