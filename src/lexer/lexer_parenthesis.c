/*
** EPITECH PROJECT, 2026
** lexer_parenthesis.c
** File description:
** Add a parenthesis
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_parenthesis(lexer_t *lexer)
{
    token_type_t type = TOKEN_LPARENTHESIS;

    if (lexer->line[lexer->pos] == ')')
        type = TOKEN_RPARENTHESIS;
    lexer->pos++;
    return create_token(type, nullptr);
}
