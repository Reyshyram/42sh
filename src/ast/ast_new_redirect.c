/*
** EPITECH PROJECT, 2026
** ast_new_redirect.c
** File description:
** Create a new redirect node
*/

#include <stdlib.h>
#include <string.h>

#include "ast.h"

ast_node_t *ast_new_redirect(ast_node_t *node, char *file, int fd, bool append)
{
    ast_node_t *new_node = malloc(sizeof(*new_node));

    if (!new_node)
        return nullptr;
    new_node->type = AST_REDIRECT;
    new_node->data.redirect.node = node;
    if (file)
        new_node->data.redirect.file = strdup(file);
    else
        new_node->data.redirect.file = nullptr;
    if (file && !new_node->data.redirect.file) {
        free(new_node);
        return nullptr;
    }
    new_node->data.redirect.fd = fd;
    new_node->data.redirect.append = append;
    return new_node;
}
