/*
** EPITECH PROJECT, 2026
** ast_new_subshell.c
** File description:
** Create a new subshell node
*/

#include <stdlib.h>

#include "ast.h"

ast_node_t *ast_new_subshell(ast_node_t *subshell)
{
    ast_node_t *node = malloc(sizeof(*node));

    if (!node)
        return nullptr;
    node->type = AST_SUBSHELL;
    node->data.subshell.node = subshell;
    return node;
}
