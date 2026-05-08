/*
** EPITECH PROJECT, 2026
** ast_new_cmd.c
** File description:
** Create a new command node
*/

#include <stdlib.h>

#include "ast.h"

ast_node_t *ast_new_cmd(char **argv, size_t argc)
{
    ast_node_t *node = malloc(sizeof(*node));

    if (!node)
        return nullptr;
    node->type = AST_CMD;
    node->data.cmd.argc = argc;
    node->data.cmd.argv = argv;
    return node;
}
