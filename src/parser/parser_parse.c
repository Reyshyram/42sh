/*
** EPITECH PROJECT, 2026
** parser_parse.c
** File description:
** Parse the tokens from the lexer
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

ast_node_t *parser_parse(parser_t *parser)
{
    ast_node_t *ast = nullptr;

    if (!skip_separators(parser))
        return nullptr;
    if (parser->current_token && parser->current_token->type == TOKEN_EOF)
        return nullptr;
    ast = parse_sequence(parser);
    if (!ast)
        return nullptr;
    if (!skip_separators(parser))
        return ast_destroy(ast), nullptr;
    if (parser->current_token && parser->current_token->type == TOKEN_EOF)
        return ast;
    if (parser->current_token
        && parser->current_token->type == TOKEN_RPARENTHESIS)
        parser_set_error(parser, "Too many )'s.");
    else
        parser_set_error(parser, "Invalid null command.");
    ast_destroy(ast);
    return nullptr;
}
