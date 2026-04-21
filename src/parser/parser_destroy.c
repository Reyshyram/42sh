/*
** EPITECH PROJECT, 2026
** parser_destroy.c
** File description:
** Free the parser
*/

#include "parser.h"
#include "token.h"

/*************************************
* The paser_destroy function frees the parsing for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *parser, structure found in include/parser.h
*************************************/

void parser_destroy(parser_t *parser)
{
    if (parser->current_token)
        token_destroy(parser->current_token);
    parser->current_token = nullptr;
}
