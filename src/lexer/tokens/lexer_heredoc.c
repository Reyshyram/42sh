/*
** EPITECH PROJECT, 2026
** lexer_heredoc.c
** File description:
** Add a heredoc
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_heredoc function adds a token for the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token
*************************************/
token_t *lexer_heredoc(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_HEREDOC, nullptr);
}
