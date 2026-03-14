/*
** EPITECH PROJECT, 2026
** lexer_redirect_append.c
** File description:
** Add a redirect append
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_redirect_append(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_REDIRECT_APPEND, nullptr);
}
