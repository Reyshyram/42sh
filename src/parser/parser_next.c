/*
** EPITECH PROJECT, 2026
** parser_next.c
** File description:
** Parse next token
*/

#include "lexer.h"
#include "parser.h"
#include "token.h"

bool parser_next(parser_t *parser)
{
    token_destroy(parser->current_token);
    parser->current_token = lexer_next_token(parser->lexer);
    if (parser->lexer->error_message) {
        parser->error_message = parser->lexer->error_message;
        return false;
    }
    if (!parser->current_token) {
        parser->error_message = "Couldn't allocate enough memory for token.";
        return false;
    }
    return true;
}
