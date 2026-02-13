/*
** EPITECH PROJECT, 2026
** parser_next.c
** File description:
** Parse next token
*/

#include "lexer.h"
#include "parser.h"
#include "token.h"

void parser_next(parser_t *parser)
{
    token_destroy(parser->current_token);
    parser->current_token = lexer_next_token(parser->lexer);
}
