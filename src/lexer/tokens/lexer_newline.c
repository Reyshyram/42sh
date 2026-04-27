/*
** EPITECH PROJECT, 2026
** lexer_newline.c
** File description:
** Add a newline
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_newline function adds a new line for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, LOGICAL_NEWLINE
*************************************/
token_t *lexer_newline(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_NEWLINE, nullptr);
}
