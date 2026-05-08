/*
** EPITECH PROJECT, 2026
** free_variable.c
** File description:
** Free a variable
*/

#include <stdlib.h>

#include "shell.h"

void free_variable(variable_t *variable)
{
    if (!variable)
        return;
    free(variable->key);
    free(variable->value);
    free(variable);
}
