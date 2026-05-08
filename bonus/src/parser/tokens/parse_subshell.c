/*
** EPITECH PROJECT, 2026
** parse_subshell.c
** File description:
** Parse a subshell
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

/*************************************
* The parse_subshell function parses a subshell for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @return -> either nullptr or a new subshell
*************************************/
ast_node_t *parse_subshell(parser_t *ps)
{
    ast_node_t *node = nullptr;

    if (!parser_next(ps))
        return nullptr;
    node = parser_parse(ps, true);
    if (!node) {
        if (!ps->error_message)
            parser_set_error(ps, "Too many ('s.");
        return nullptr;
    }
    if (!ps->current_token || ps->current_token->type != TOKEN_RPARENTHESIS) {
        ast_destroy(node);
        parser_set_error(ps, "Too many ('s.");
        return nullptr;
    }
    if (!parser_next(ps)) {
        ast_destroy(node);
        return nullptr;
    }
    return ast_new_subshell(node);
}
