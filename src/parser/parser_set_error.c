/*
** EPITECH PROJECT, 2026
** parser_set_error
** File description:
** Set parser error
*/

#include "parser.h"

void parser_set_error(parser_t *parser, char *error_message)
{
    if (!parser->error_message)
        parser->error_message = error_message;
}
