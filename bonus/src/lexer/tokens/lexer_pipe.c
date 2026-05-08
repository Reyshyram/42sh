/*
** EPITECH PROJECT, 2026
** lexer_pipe.c
** File description:
** Add a pipe
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_pipe(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_PIPE, nullptr);
}
