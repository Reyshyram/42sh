/*
** EPITECH PROJECT, 2026
** lexer_redirect_out.c
** File description:
** Add a redirect out
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_redirect_out function adds the redir out for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, TOKEN_REDIRECT_OUT
*************************************/
token_t *lexer_redirect_out(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_REDIRECT_OUT, nullptr);
}
