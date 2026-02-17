/*
** EPITECH PROJECT, 2026
** parse_sequence.c
** File description:
** Parse a sequence of commands
*/

#include "ast.h"
#include "parser.h"

ast_node_t *parse_sequence(parser_t *parser)
{
    ast_node_t *left = parse_command_start(parser);

    return left;
}
