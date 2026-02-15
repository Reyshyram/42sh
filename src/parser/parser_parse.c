/*
** EPITECH PROJECT, 2026
** parser_parse.c
** File description:
** Parse the tokens from the lexer
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

static bool is_separator(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_NEWLINE || token->type == TOKEN_SEMICOLON;
}

static bool skip_separators(parser_t *parser)
{
    while (is_separator(parser->current_token))
        if (!parser_next(parser))
            return false;
    return true;
}

static ast_node_t *parser_tokens(parser_t *parser)
{
    ast_node_t *node = nullptr;

    if (!skip_separators(parser))
        return nullptr;
    if (parser->current_token && parser->current_token->type == TOKEN_EOF)
        return nullptr;
    return node;
}

ast_node_t *parser_parse(parser_t *parser)
{
    ast_node_t *ast = parser_tokens(parser);

    if (!ast) {
        if (parser->error_message)
            return nullptr;
        if (parser->current_token && parser->current_token->type == TOKEN_EOF)
            return nullptr;
        parser->error_message = "Unexpected token.";
        return nullptr;
    }
    if (!parser->current_token || parser->current_token->type != TOKEN_EOF) {
        parser->error_message = "Unexpected ending token.";
        ast_destroy(ast);
        return nullptr;
    }
    return ast;
}
