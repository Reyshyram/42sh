/*
** EPITECH PROJECT, 2025
** my_str_islower
** File description:
** Checks if a string is only using lowercase letters
*/

#include <stddef.h>

#include "my/strings.h"

bool my_str_islower(const char *str)
{
    for (size_t i = 0; i < my_strlen(str); i++)
        if (!my_islower(str[i]))
            return false;
    return true;
}
