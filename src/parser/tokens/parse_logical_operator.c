/*
** EPITECH PROJECT, 2026
** parse_logical_operator.c
** File description:
** Parse a logical operator
*/

#include "ast.h"
#include "parser.h"

static void handle_memory_error(parser_t *parser, ast_node_t *left,
    ast_node_t *right)
{
    ast_destroy(left);
    ast_destroy(right);
    parser_set_error(parser, "Couldn't allocate enough memory for AST.");
}

static bool add_logical_node(parser_t *parser, ast_node_t **left)
{
    ast_node_t *right = nullptr;
    ast_node_t *new_left = nullptr;
    ast_type_t type = get_logical_type(parser->current_token->type);

    if (!parser_next(parser)) {
        ast_destroy(*left);
        return false;
    }
    right = parse_sequence_start(parser);
    if (!right) {
        ast_destroy(*left);
        return false;
    }
    new_left = ast_new_binary(type, *left, right);
    if (!new_left) {
        handle_memory_error(parser, *left, right);
        return false;
    }
    *left = new_left;
    return true;
}

ast_node_t *parse_logical_operator(parser_t *parser)
{
    ast_node_t *left = nullptr;

    left = parse_sequence_start(parser);
    if (!left)
        return nullptr;
    while (is_logical_token(parser->current_token))
        if (!add_logical_node(parser, &left))
            return nullptr;
    return left;
}
