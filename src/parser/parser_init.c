/*
** EPITECH PROJECT, 2026
** parser_init.c
** File description:
** Initialize the parser
*/

#include "lexer.h"
#include "parser.h"

void parser_init(parser_t *parser, lexer_t *lexer)
{
    parser->lexer = lexer;
    parser->current_token = nullptr;
    parser->error_message = nullptr;
    parser->error_message_prefix = nullptr;
    parser_next(parser);
}
