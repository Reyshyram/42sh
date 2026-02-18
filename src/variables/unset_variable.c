/*
** EPITECH PROJECT, 2026
** unset_variable.c
** File description:
** Unset a variable
*/

#include "my/list.h"
#include "my/strings.h"

#include "shell.h"

void unset_variable(linked_list_t *variables, char *key)
{
    linked_list_t *prev = nullptr;
    linked_list_t *curr = variables;
    variable_t *data = nullptr;

    if (!variables || !key)
        return;
    while (curr) {
        data = curr->data;
        if (!my_strcmp(data->key, key)) {
            my_delete_node(&variables, curr, prev, (void *) free_variable);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}
