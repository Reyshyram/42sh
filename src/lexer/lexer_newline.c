/*
** EPITECH PROJECT, 2026
** lexer_newline.c
** File description:
** Add a newline
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_newline(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_NEWLINE, nullptr);
}
