/*
** EPITECH PROJECT, 2026
** execute_repeat.c
** File description:
** Repeat a command multiple times
*/

#include "ast.h"
#include "executer.h"
#include "shell.h"

/*************************************
* The execute_repeat function executes the repeat for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either a success or an error
*************************************/
int execute_repeat(shell_t *shell, ast_node_t *ast)
{
    int status = 0;

    for (int i = 0; i < ast->data.repeat.count; i++)
        status = execute_ast(shell, ast->data.repeat.node);
    return status;
}
