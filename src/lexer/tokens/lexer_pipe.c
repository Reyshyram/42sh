/*
** EPITECH PROJECT, 2026
** lexer_pipe.c
** File description:
** Add a pipe
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_pipe function adds a pipe for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, TOKEN_PIPE
*************************************/
token_t *lexer_pipe(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_PIPE, nullptr);
}
