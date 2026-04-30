/*
** EPITECH PROJECT, 2026
** lexer_redirect_in.c
** File description:
** Add a redirect in
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_redirect_in function adds the redir in for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, TOKEN_REDIRECT_IN
*************************************/
token_t *lexer_redirect_in(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_REDIRECT_IN, nullptr);
}
