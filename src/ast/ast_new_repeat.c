/*
** EPITECH PROJECT, 2026
** ast_new_repeat.c
** File description:
** Add a new repeat node
*/

#include <stdlib.h>

#include "ast.h"

ast_node_t *ast_new_repeat(ast_node_t *node, int count)
{
    ast_node_t *new_node = malloc(sizeof(*new_node));

    if (!new_node)
        return nullptr;
    new_node->type = AST_REPEAT;
    new_node->data.repeat.node = node;
    new_node->data.repeat.count = count;
    return new_node;
}
