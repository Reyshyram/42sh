/*
** EPITECH PROJECT, 2025
** parser.h
** File description:
** Parser related things, convert tokens into nodes
*/

#ifndef PARSER_H
// clang-format off
    #define PARSER_H

    #include "lexer.h"
    #include "token.h"
// clang-format on

typedef struct parser {
    lexer_t *lexer;
    token_t *current_token;
    char *error_message;
} parser_t;

void parser_init(parser_t *parser, lexer_t *lexer);

#endif /* PARSER_H */
