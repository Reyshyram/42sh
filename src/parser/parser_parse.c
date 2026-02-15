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

    if (!ast) {
        if (parser->error_message)
            return nullptr;
        if (parser->current_token && parser->current_token->type == TOKEN_EOF)
            return nullptr;
        parser->error_message = "Unexpected token.";
        return nullptr;
    }
    if (parser->current_token->type != TOKEN_EOF) {
        parser->error_message = "Unexpected ending token.";
        ast_destroy(ast);
        return nullptr;
    }
    return ast;
}
