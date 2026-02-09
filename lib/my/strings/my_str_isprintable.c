/*
** EPITECH PROJECT, 2025
** my_str_isprintable
** File description:
** Check if a string is only using printable characters
*/

#include <stddef.h>

#include "my/strings.h"

bool my_str_isprintable(const char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (!my_isprintable(str[i]))
            return false;
    return true;
}
