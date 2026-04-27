/*
** EPITECH PROJECT, 2026
** free_variable.c
** File description:
** Free a variable
*/

#include <stdlib.h>

#include "shell.h"

/*************************************
* The free_variable function frees the memory of the variable for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> variable_t *variable, structure found in include/shell.h
*************************************/
void free_variable(variable_t *variable)
{
    if (!variable)
        return;
    free(variable->key);
    free(variable->value);
    free(variable);
}
