/*
** EPITECH PROJECT, 2026
** env_get_value
** File description:
** Get the value of an environmental variable
*/

#include <stddef.h>

#include "my/strings.h"

char *env_get_value(char **env, char *key)
{
    size_t key_length = my_strlen(key);

    for (size_t i = 0; env[i]; i++)
        if (!my_strncmp(env[i], key, key_length) && env[i][key_length] == '=')
            return env[i] + key_length + 1;
    return nullptr;
}
