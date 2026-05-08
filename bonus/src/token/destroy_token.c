/*
** EPITECH PROJECT, 2026
** destroy_token.c
** File description:
** Destroy a token
*/

#include <stdlib.h>

#include "token.h"

void token_destroy(token_t *token)
{
    if (!token)
        return;
    if (token->value)
        free(token->value);
    free(token);
}
