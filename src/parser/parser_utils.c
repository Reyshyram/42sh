/*
** EPITECH PROJECT, 2026
** parser_utils
** File description:
** utilities for parser
*/

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
