/*
** EPITECH PROJECT, 2025
** parser.h
** File description:
** Parser related things, convert tokens into nodes
*/

#ifndef PARSER_H
// clang-format off
    #define PARSER_H

    #include "ast.h"
    #include "lexer.h"
    #include "token.h"
// clang-format on

typedef struct parser {
    lexer_t *lexer;
    token_t *current_token;
    char *error_message;
} parser_t;

void parser_init(parser_t *parser, lexer_t *lexer);
bool parser_next(parser_t *parser);
void parser_destroy(parser_t *parser);
void parser_set_error(parser_t *parser, char *error_message);

bool is_separator(token_t *token);
bool skip_separators(parser_t *parser);

ast_node_t *parser_parse(parser_t *parser);
ast_node_t *parse_sequence(parser_t *parser);
ast_node_t *parse_command_start(parser_t *parser);

#endif /* PARSER_H */
