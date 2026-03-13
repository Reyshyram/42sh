/*
** EPITECH PROJECT, 2026
** lexer_semicolon.c
** File description:
** Add a semicolon
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_semicolon(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_SEMICOLON, nullptr);
}
