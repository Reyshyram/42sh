/*
** EPITECH PROJECT, 2026
** lexer_logical_and.c
** File description:
** Add a logical_and
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_logical_and(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_LOGICAL_AND, nullptr);
}
