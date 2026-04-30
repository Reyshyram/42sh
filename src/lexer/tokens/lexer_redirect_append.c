/*
** EPITECH PROJECT, 2026
** lexer_redirect_append.c
** File description:
** Add a redirect append
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_redirect_append function appends the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, TOKEN_REDIRECT_APPEND
*************************************/
token_t *lexer_redirect_append(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_REDIRECT_APPEND, nullptr);
}
