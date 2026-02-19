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
    #include <sys/types.h>

    #include "shell.h"
    #include "token.h"
// clang-format on

typedef struct lexer {
    char *error_message;
    char *error_message_prefix;
    char *line;
    size_t pos;
    shell_t *shell;
} lexer_t;

struct lexer_reader {
    char *buffer;
    size_t buffer_size;
    bool in_double_quotes;
};

bool lexer_is_word_separator(char c);

void lexer_init(lexer_t *lexer, char *line, shell_t *shell);
token_t *lexer_next_token(lexer_t *lexer);

token_t *lexer_newline(lexer_t *lexer);
token_t *lexer_parenthesis(lexer_t *lexer);
token_t *lexer_semicolon(lexer_t *lexer);
token_t *lexer_logical_and(lexer_t *lexer);
token_t *lexer_logical_or(lexer_t *lexer);
token_t *lexer_word(lexer_t *lexer);

bool lexer_expand_variable(lexer_t *lexer, struct lexer_reader *reader);
bool lexer_expand_tilde(lexer_t *lexer, struct lexer_reader *reader);

bool lexer_set_alloc_error(lexer_t *lexer);
bool lexer_append_str(lexer_t *lexer, struct lexer_reader *reader, char *str,
    ssize_t str_length);
bool lexer_append_current_char(lexer_t *lexer, struct lexer_reader *reader);

#endif /* LEXER_H */
