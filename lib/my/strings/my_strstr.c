/*
** EPITECH PROJECT, 2025
** my_strstr
** File description:
** Check if the given substring is present in the source string
*/

#include <stddef.h>

#include "my/strings.h"

char *my_strstr(char *str, const char *to_find)
{
    size_t to_find_length = my_strlen(to_find);

    if (to_find_length == 0)
        return str;
    for (size_t i = 0; i <= my_strlen(str) - to_find_length; i++)
        if (my_strncmp(str + i, to_find, to_find_length) == 0)
            return str + i;
    return 0;
}
