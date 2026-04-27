/*
** EPITECH PROJECT, 2026
** parse_sequence.c
** File description:
** Parse a sequence of commands
*/

#include "ast.h"
#include "parser.h"

/*************************************
* The add_sequence_node function adds a node for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *parser, structure found in include/parser.h
*   @param -> ast_node_t **left, structure found in include/ast.h
*   @return -> a boolean, either true or false
*************************************/
static bool add_sequence_node(parser_t *parser, ast_node_t **left)
{
    ast_node_t *right = nullptr;
    ast_node_t *new_left = nullptr;

    right = parse_logical_operator(parser);
    if (!right) {
        ast_destroy(*left);
        return false;
    }
    new_left = ast_new_binary(AST_SEQUENCE, *left, right);
    if (!new_left) {
        ast_destroy(*left);
        ast_destroy(right);
        parser_set_error(parser, "Couldn't allocate enough memory for AST.");
        return false;
    }
    *left = new_left;
    return true;
}

/*************************************
* The parse_sequence function parses a sequence for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *parser, structure found in include/parser.h
*   @return -> either the left node or nullptr
*************************************/
ast_node_t *parse_sequence(parser_t *parser)
{
    ast_node_t *left = nullptr;

    left = parse_logical_operator(parser);
    if (!left)
        return nullptr;
    while (is_separator(parser->current_token)) {
        if (!skip_separators(parser))
            return ast_destroy(left), nullptr;
        if (is_sequence_end(parser->current_token))
            return left;
        if (!add_sequence_node(parser, &left))
            return nullptr;
    }
    return left;
}
