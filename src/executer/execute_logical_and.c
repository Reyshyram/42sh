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

/*************************************
* The execute_logical_and function executes the
* logical and for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, an error or a success
*************************************/
int execute_logical_and(shell_t *shell, ast_node_t *ast)
{
    int status = execute_ast(shell, ast->data.binary.left);

    if (status != SUCCESS)
        return status;
    return execute_ast(shell, ast->data.binary.right);
}
