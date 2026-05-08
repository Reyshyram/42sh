/*
** EPITECH PROJECT, 2026
** get_variable.c
** File description:
** Get a variable
*/

#include <string.h>

#include "my/list.h"

#include "shell.h"

variable_t *get_variable(linked_list_t *variables, char *key)
{
    variable_t *data = nullptr;

    if (!variables || !key)
        return nullptr;
    for (linked_list_t *node = variables; node; node = node->next) {
        data = node->data;
        if (!strcmp(data->key, key))
            return data;
    }
    return nullptr;
}
