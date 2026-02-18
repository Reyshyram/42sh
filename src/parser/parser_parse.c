/*
** EPITECH PROJECT, 2026
** parser_parse.c
** File description:
** Parse the tokens from the lexer
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

static bool prepare_parser(parser_t *ps, bool in_subshell)
{
    if (!skip_separators(ps))
        return false;
    if (ps->current_token && ps->current_token->type == TOKEN_EOF)
        return false;
    if (!in_subshell && ps->current_token
        && ps->current_token->type == TOKEN_RPARENTHESIS) {
        parser_set_error(ps, "Too many )'s.");
        return false;
    }
    return true;
}

ast_node_t *parser_parse(parser_t *ps, bool in_subshell)
{
    ast_node_t *ast = nullptr;

    if (!prepare_parser(ps, in_subshell))
        return nullptr;
    ast = parse_sequence(ps);
    if (!ast)
        return nullptr;
    if (!skip_separators(ps))
        return ast_destroy(ast), nullptr;
    if (ps->current_token->type == TOKEN_EOF
        || (in_subshell && ps->current_token->type == TOKEN_RPARENTHESIS))
        return ast;
    if (ps->current_token && ps->current_token->type == TOKEN_RPARENTHESIS)
        parser_set_error(ps, "Too many )'s.");
    else
        parser_set_error(ps, "Invalid null command.");
    ast_destroy(ast);
    return nullptr;
}
