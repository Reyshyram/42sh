/*
** EPITECH PROJECT, 2026
** lexer_next_token.c
** File description:
** Get the next token
*/

#include "my/strings.h"

#include "lexer.h"
#include "token.h"

static void skip_spaces_and_tabs(lexer_t *lexer)
{
    while (lexer->line[lexer->pos] == ' ' || lexer->line[lexer->pos] == '\t')
        lexer->pos++;
}

token_t *lexer_next_token(lexer_t *lexer)
{
    skip_spaces_and_tabs(lexer);
    if (!lexer->line[lexer->pos])
        return create_token(TOKEN_EOF, nullptr);
    if (lexer->line[lexer->pos] == '\n')
        return lexer_newline(lexer);
    if (lexer->line[lexer->pos] == '(' || lexer->line[lexer->pos] == ')')
        return lexer_parenthesis(lexer);
    if (lexer->line[lexer->pos] == ';')
        return lexer_semicolon(lexer);
    if (!my_strncmp(&lexer->line[lexer->pos], "&&", 2))
        return lexer_logical_and(lexer);
    if (!my_strncmp(&lexer->line[lexer->pos], "||", 2))
        return lexer_logical_or(lexer);
    if (lexer->line[lexer->pos] == '|')
        return lexer_pipe(lexer);
    return lexer_word(lexer);
}
