/*
** EPITECH PROJECT, 2026
** ast_new_cmd.c
** File description:
** Create a new command node
*/

#include <stdlib.h>

#include "ast.h"

/*************************************
* The ast_new_cmd function adds a new command for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char **argv, an array of args
*   @param -> size_t argc, the length of the arg
*   @return -> a node
*************************************/
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
