/*
** EPITECH PROJECT, 2026
** parser_set_error
** File description:
** Set parser error
*/

#include "parser.h"

/*************************************
* The parset_set_error function sets the errors for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *parser, structure found in include/parser.h
*   @entry_parameter -> char *error_message, an error message
*************************************/

void parser_set_error(parser_t *parser, char *error_message)
{
    if (!parser->error_message)
        parser->error_message = error_message;
}
