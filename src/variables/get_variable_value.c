/*
** EPITECH PROJECT, 2026
** get_variable_value.c
** File description:
** Get the value of a variable
*/

#include "my/list.h"

#include "shell.h"

char *get_variable_value(linked_list_t *variables, char *key)
{
    variable_t *data = get_variable(variables, key);

    if (!data)
        return nullptr;
    return data->value;
}
