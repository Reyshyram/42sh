/*
** EPITECH PROJECT, 2026
** create_token.c
** File description:
** Create a new token
*/

#include <stdlib.h>
#include "token.h"

/*************************************
* The create_token function destroys the token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> token_type_t type, structure found in include/token.h
*   @param -> char *value, a string
*   @return -> either the token or nullptr
*************************************/
token_t *create_token(token_type_t type, char *value)
{
    token_t *token = malloc(sizeof(*token));

    if (!token) {
        if (value)
            free(value);
        return nullptr;
    }
    token->type = type;
    token->value = value;
    return token;
}
