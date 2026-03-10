/*
** EPITECH PROJECT, 2026
** ast_destroy.c
** File description:
** Free the ast
*/

#include <stdlib.h>

#include "my/misc.h"

#include "ast.h"

void ast_destroy(ast_node_t *ast)
{
    if (!ast)
        return;
    if (ast->type == AST_CMD)
        my_free_word_array(ast->data.cmd.argv);
    if (ast->type == AST_SEQUENCE || ast->type == AST_LOGICAL_AND
        || ast->type == AST_LOGICAL_OR || ast->type == AST_PIPE) {
        ast_destroy(ast->data.binary.left);
        ast_destroy(ast->data.binary.right);
    }
    if (ast->type == AST_SUBSHELL)
        ast_destroy(ast->data.subshell.node);
    free(ast);
}
