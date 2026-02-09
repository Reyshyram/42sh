/*
** EPITECH PROJECT, 2025
** my_getnbr_base
** File description:
** Convert a string into an int using a specified base
*/

#include <stddef.h>

#include "my/strings.h"

static bool is_in_base(char c, const char *base)
{
    while (*base) {
        if (c == *base)
            return true;
        base++;
    }
    return false;
}

__int128_t my_getnbr_base(const char *str, const char *base)
{
    int sign = 1;
    size_t n = my_strlen(base);
    __int128_t nb = 0;

    while (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -sign;
        str++;
    }
    while (is_in_base(*str, base)) {
        nb = (nb * (int) n) + my_getindex(*str, base);
        str++;
    }
    return nb * sign;
}
