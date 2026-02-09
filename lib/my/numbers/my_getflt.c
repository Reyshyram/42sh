/*
** EPITECH PROJECT, 2025
** my_getflt.c
** File description:
** Get the float from a string
*/

#include <stdint.h>

#include "my/strings.h"

float my_getflt(const char *str)
{
    int8_t sign = 1;
    float nb = 0;

    while (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = (int8_t) -sign;
        str++;
    }
    while (my_isnumber(*str)) {
        nb = nb * 10 + (float) *str - '0';
        str++;
    }
    if (*str != '.')
        return nb;
    str++;
    for (uint64_t i = 10; my_isnumber(*str); i *= 10) {
        nb += ((float) *str - '0') / (float) i;
        str++;
    }
    return nb;
}
