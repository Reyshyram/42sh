/*
** EPITECH PROJECT, 2026
** lexer_parenthesis.c
** File description:
** Add a parenthesis
*/

#include "lexer.h"
#include "token.h"

/*************************************
* The lexer_parenthesis function adds parenthesis for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a new token for parenthesis
*************************************/
token_t *lexer_parenthesis(lexer_t *lexer)
{
    token_type_t type = TOKEN_LPARENTHESIS;

    if (lexer->line[lexer->pos] == ')')
        type = TOKEN_RPARENTHESIS;
    lexer->pos++;
    return create_token(type, nullptr);
}
