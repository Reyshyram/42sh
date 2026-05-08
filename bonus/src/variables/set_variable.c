/*
** EPITECH PROJECT, 2026
** set_variable.c
** File description:
** Set a variable
*/

#include <stdlib.h>
#include <string.h>

#include "my/list.h"

#include "shell.h"

static bool update_existing_variable(variable_t *variable, char *value)
{
    char *temp = strdup(value);

    if (!temp)
        return false;
    free(variable->value);
    variable->value = temp;
    return true;
}

static bool fill_data(variable_t *variable, char *key, char *value)
{
    variable->key = strdup(key);
    if (!variable->key) {
        free(variable);
        return false;
    }
    variable->value = strdup(value);
    if (!variable->value) {
        free(variable->key);
        free(variable);
        return false;
    }
    return true;
}

bool set_variable(linked_list_t **variables, char *key, char *value)
{
    variable_t *variable = nullptr;
    variable_t *found_variable = nullptr;

    if (!key || !value)
        return false;
    found_variable = get_variable(*variables, key);
    if (found_variable)
        return update_existing_variable(found_variable, value);
    variable = malloc(sizeof(*variable));
    if (!variable)
        return false;
    if (!fill_data(variable, key, value))
        return false;
    if (!my_add_to_list(variables, variable)) {
        free_variable(variable);
        return false;
    }
    return true;
}
