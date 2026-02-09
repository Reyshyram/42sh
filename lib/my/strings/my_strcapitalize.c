/*
** EPITECH PROJECT, 2025
** my_strcapitalize
** File description:
** Capitalize every word of the given string
*/

#include <stddef.h>

#include "my/strings.h"

static bool should_capitalize_after(char c)
{
    return (
        c == '-' || c == ',' || c == ' ' || c == '?' || c == ';' || c == '+');
}

char *my_strcapitalize(char *str)
{
    bool capitalize = true;

    for (size_t i = 0; i < my_strlen(str); i++) {
        if (my_isupper(str[i]) && !capitalize)
            str[i] += 'a' - 'A';
        if (my_isupper(str[i]))
            capitalize = false;
        if (my_islower(str[i]) && capitalize) {
            str[i] -= 'a' - 'A';
            capitalize = true;
        }
        if (my_isnumber(str[i]))
            capitalize = false;
        if (should_capitalize_after(str[i]))
            capitalize = true;
    }
    return str;
}
