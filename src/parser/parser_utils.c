/*
** EPITECH PROJECT, 2026
** parser_utils
** File description:
** utilities for parser
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

bool is_separator(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_NEWLINE || token->type == TOKEN_SEMICOLON;
}

bool skip_separators(parser_t *parser)
{
    while (is_separator(parser->current_token))
        if (!parser_next(parser))
            return false;
    return true;
}

bool is_logical_token(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_LOGICAL_AND || token->type == TOKEN_LOGICAL_OR;
}

ast_type_t get_logical_type(token_type_t type)
{
    if (type == TOKEN_LOGICAL_AND)
        return AST_LOGICAL_AND;
    return AST_LOGICAL_OR;
}

bool is_sequence_end(token_t *token)
{
    if (!token)
        return true;
    return token->type == TOKEN_EOF || token->type == TOKEN_RPARENTHESIS;
}
