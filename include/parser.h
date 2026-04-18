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
    char *error_message_prefix;
} parser_t;

void parser_init(parser_t *parser, lexer_t *lexer);
bool parser_next(parser_t *parser);
void parser_destroy(parser_t *parser);
void parser_set_error(parser_t *parser, char *error_message);

bool is_separator(token_t *token);
bool skip_separators(parser_t *parser);
bool is_logical_token(token_t *token);
ast_type_t get_logical_type(token_type_t type);
bool is_sequence_end(token_t *token);

ast_node_t *parser_parse(parser_t *ps, bool in_subshell);
ast_node_t *parse_sequence_start(parser_t *parser);
ast_node_t *parse_sequence(parser_t *parser);
ast_node_t *parse_logical_operator(parser_t *parser);
bool parser_glob(parser_t *ps, char ***argv, size_t *argc);
ast_node_t *parse_command(parser_t *ps);
ast_node_t *parse_subshell(parser_t *ps);

#endif /* PARSER_H */
