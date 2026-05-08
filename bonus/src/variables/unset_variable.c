/*
** EPITECH PROJECT, 2026
** unset_variable.c
** File description:
** Unset a variable
*/

#include <string.h>

#include "my/list.h"

#include "shell.h"

void unset_variable(linked_list_t **variables, char *key)
{
    linked_list_t *prev = nullptr;
    linked_list_t *curr = nullptr;
    variable_t *data = nullptr;

    if (!variables || !*variables || !key)
        return;
    curr = *variables;
    while (curr) {
        data = curr->data;
        if (!strcmp(data->key, key)) {
            my_delete_node(variables, curr, prev, (void *) free_variable);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
