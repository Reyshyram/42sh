/*
** EPITECH PROJECT, 2026
** get_variable_value.c
** File description:
** Get the value of a variable
*/

#include "my/list.h"

#include "shell.h"

/*************************************
* The get_variable_value function gets the value of a data for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> linked_list_t *variables, structure found in include/shell.h
*   @param -> char *key, a string of the key
*   @return -> either the value or nullptr
*************************************/
char *get_variable_value(linked_list_t *variables, char *key)
{
    variable_t *data = get_variable(variables, key);

    if (!data)
        return nullptr;
    return data->value;
}
