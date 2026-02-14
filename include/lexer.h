/*
** EPITECH PROJECT, 2025
** lexer.h
** File description:
** Lexer related things, convert input into tokens
*/

#ifndef LEXER_H
// clang-format off
    #define LEXER_H

    #include <stddef.h>

    #include "shell.h"
    #include "token.h"
// clang-format on

typedef struct lexer {
    char *error_message;
    char *line;
    size_t pos;
    shell_t *shell;
} lexer_t;

void lexer_init(lexer_t *lexer, char *line, shell_t *shell);
token_t *lexer_next_token(lexer_t *lexer);

token_t *lexer_newline(lexer_t *lexer);
token_t *lexer_parenthesis(lexer_t *lexer);
token_t *lexer_semicolon(lexer_t *lexer);
token_t *lexer_logical_and(lexer_t *lexer);
token_t *lexer_logical_or(lexer_t *lexer);
token_t *lexer_word(lexer_t *lexer);

#endif /* LEXER_H */
