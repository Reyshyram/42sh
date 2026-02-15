/*
** EPITECH PROJECT, 2026
** parser_destroy.c
** File description:
** Free the parser
*/

#include "parser.h"
#include "token.h"

void parser_destroy(parser_t *parser)
{
    if (parser->current_token)
        token_destroy(parser->current_token);
    parser->current_token = nullptr;
}
