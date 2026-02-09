/*
** EPITECH PROJECT, 2025
** my_strcmp
** File description:
** Compare two strings
*/

#include <stddef.h>

#include "my/strings.h"

int my_strcmp(const char *s1, const char *s2)
{
    size_t s1_len = my_strlen(s1);
    size_t s2_len = my_strlen(s2);
    size_t max_len = s2_len;

    if (s1_len > s2_len)
        max_len = s1_len;
    return my_strncmp(s1, s2, max_len);
}
