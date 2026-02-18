/*
** EPITECH PROJECT, 2026
** env_get_value
** File description:
** Get the value of an environmental variable
*/

#include <stddef.h>

#include "my/list.h"
#include "my/strings.h"

char *env_get_value(linked_list_t *env, char *key)
{
    size_t key_length = my_strlen(key);
    char *data = nullptr;

    for (linked_list_t *node = env; node; node = node->next) {
        data = node->data;
        if (!my_strncmp(data, key, key_length) && data[key_length] == '=')
            return data + key_length + 1;
    }
    return nullptr;
}
