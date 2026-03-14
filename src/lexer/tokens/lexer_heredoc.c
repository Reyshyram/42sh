/*
** EPITECH PROJECT, 2026
** lexer_heredoc.c
** File description:
** Add a heredoc
*/

#include "lexer.h"
#include "token.h"

token_t *lexer_heredoc(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_HEREDOC, nullptr);
}
