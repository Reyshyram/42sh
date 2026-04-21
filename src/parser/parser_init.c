/*
** EPITECH PROJECT, 2026
** parser_init.c
** File description:
** Initialize the parser
*/

#include "lexer.h"
#include "parser.h"

/*************************************
* The parser_init function initialises the parsing for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *parser, structure found in include/parser.h
*   @entry_parameter -> lexer_t *lexer, structure in include/lexer.h
*************************************/

void parser_init(parser_t *parser, lexer_t *lexer)
{
    parser->lexer = lexer;
    parser->current_token = nullptr;
    parser->error_message = nullptr;
    parser->error_message_prefix = nullptr;
    parser_next(parser);
}
