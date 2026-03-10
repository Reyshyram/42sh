/*
** EPITECH PROJECT, 2025
** token.h
** File description:
** Tokens for the lexer and parser
*/

#ifndef TOKEN_H
// clang-format off
    #define TOKEN_H
// clang-format on

typedef enum {
    TOKEN_EOF,
    TOKEN_WORD,
    TOKEN_NEWLINE,
    TOKEN_SEMICOLON,
    TOKEN_LPARENTHESIS,
    TOKEN_RPARENTHESIS,
    TOKEN_LOGICAL_AND,
    TOKEN_LOGICAL_OR,
    TOKEN_PIPE,
} token_type_t;

typedef struct token {
    token_type_t type;
    char *value;
} token_t;

token_t *create_token(token_type_t type, char *value);
void token_destroy(token_t *token);

#endif /* TOKEN_H */
