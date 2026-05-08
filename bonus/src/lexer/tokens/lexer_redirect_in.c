/*
** EPITECH PROJECT, 2026
** lexer_redirect_in.c
** File description:
** Add a redirect in
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_redirect_in(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_REDIRECT_IN, nullptr);
}
