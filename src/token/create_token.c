/*
** EPITECH PROJECT, 2026
** create_token.c
** File description:
** Create a new token
*/

#include <stdlib.h>

#include "token.h"

// Use already malloced value
token_t *create_token(token_type_t type, char *value)
{
    token_t *token = malloc(sizeof(*token));

    if (!token) {
        free(value);
        return nullptr;
    }
    token->type = type;
    token->value = value;
    return token;
}
