/*
** EPITECH PROJECT, 2026
** parser_next.c
** File description:
** Parse next token
*/

#include "lexer.h"
#include "parser.h"
#include "token.h"

/*************************************
* The parser_next function parses the next token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *parser, structure found in include/parser.h
*   @return_parameter -> a boolean, either true or false
*************************************/

bool parser_next(parser_t *parser)
{
    token_destroy(parser->current_token);
    parser->current_token = lexer_next_token(parser->lexer);
    if (parser->lexer->error_message) {
        parser->error_message_prefix = parser->lexer->error_message_prefix;
        parser->error_message = parser->lexer->error_message;
        return false;
    }
    if (!parser->current_token) {
        parser->error_message = "Couldn't allocate enough memory for token.";
        return false;
    }
    return true;
}
