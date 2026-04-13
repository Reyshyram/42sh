/*
** EPITECH PROJECT, 2026
** env_to_list.c
** File description:
** Transform env into a linked list
*/

#include <stdlib.h>
#include <string.h>

#include "my/list.h"
#include "my/strings.h"

#include "shell.h"

linked_list_t *env_to_list(char **env)
{
    linked_list_t *head = nullptr;
    size_t key_length = 0;
    variable_t *variable = nullptr;

    for (size_t i = 0; env[i]; i++) {
        key_length = my_getindex('=', env[i]);
        variable = malloc(sizeof(*variable));
        if (!variable)
            return my_free_list(head, (void *) free_variable), nullptr;
        variable->key = strndup(env[i], key_length);
        variable->value = strdup(env[i] + key_length + 1);
        if (!variable->key || !variable->value) {
            free(variable->value);
            free(variable->key);
            return my_free_list(head, (void *) free_variable), nullptr;
        }
        if (!my_add_to_list(&head, variable))
            return my_free_list(head, (void *) free_variable), nullptr;
    }
    return head;
}
