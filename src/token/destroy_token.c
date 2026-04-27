/*
** EPITECH PROJECT, 2026
** destroy_token.c
** File description:
** Destroy a token
*/

#include <stdlib.h>
#include "token.h"

/*************************************
* The token_destroy function destroys the token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> token_t *token, structure found in include/token.h
*************************************/
void token_destroy(token_t *token)
{
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}
