/*
** EPITECH PROJECT, 2026
** lexer_logical_or.c
** File description:
** Add a logical_or
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_logical_or(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_LOGICAL_OR, nullptr);
}
