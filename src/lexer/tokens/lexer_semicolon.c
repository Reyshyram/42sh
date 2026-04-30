/*
** EPITECH PROJECT, 2026
** lexer_semicolon.c
** File description:
** Add a semicolon
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_semicolon function adds a semicolon for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token, TOKEN_SEMICOLON
*************************************/
token_t *lexer_semicolon(lexer_t *lexer)
{
    lexer->pos++;
    return create_token(TOKEN_SEMICOLON, nullptr);
}
