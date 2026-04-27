/*
** EPITECH PROJECT, 2026
** unset_variable.c
** File description:
** Unset a variable
*/

#include <string.h>

#include "my/list.h"

#include "shell.h"

/*************************************
* The unset_variable function unsets the content of a data
* within its variable for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> linked_list_t **variables, an array of the structure found
*             in include/shell.h
*   @param -> char *key, the key of the data
*************************************/
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
