/*
** EPITECH PROJECT, 2026
** execute_ast.c
** File description:
** Execute the command following the ast
*/

#include <stdio.h>

#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

/*************************************
* The execute_ast function executes the ast for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> ast_node_t *ast, a structure found in include/ast.h
*   @return -> an int, either a success or an error
*************************************/
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
    if (ast->type == AST_REPEAT)
        return execute_repeat(shell, ast);
    if (ast->type == AST_PIPE)
        return execute_pipe(shell, ast);
    if (ast->type == AST_SUBSHELL)
        return execute_subshell(shell, ast);
    if (ast->type == AST_REDIRECT)
        return execute_redirect(shell, ast);
    fprintf(stderr, "Unknown AST node encountered in the executor.\n");
    return ERROR;
}
