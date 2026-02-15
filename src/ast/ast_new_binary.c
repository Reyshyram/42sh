/*
** EPITECH PROJECT, 2026
** ast_new_binary.c
** File description:
** Create a new binary node
*/

#include <stdlib.h>

#include "ast.h"

ast_node_t *ast_new_binary(ast_type_t type, ast_node_t *left,
    ast_node_t *right)
{
    ast_node_t *node = malloc(sizeof(*node));

    if (!node)
        return nullptr;
    node->type = type;
    node->data.binary.left = left;
    node->data.binary.right = right;
    return node;
}
