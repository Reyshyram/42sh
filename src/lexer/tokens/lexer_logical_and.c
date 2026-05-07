/*
** EPITECH PROJECT, 2026
** lexer_logical_and.c
** File description:
** Add a logical_and
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_logical_and function adds an "and" for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, LOGICAL_AND
*************************************/
token_t *lexer_logical_and(lexer_t *lexer)
{
    lexer->pos += 2;
    return create_token(TOKEN_LOGICAL_AND, nullptr);
}
