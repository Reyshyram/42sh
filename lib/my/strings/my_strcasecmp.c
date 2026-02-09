/*
** EPITECH PROJECT, 2025
** my_strcasecmp
** File description:
** Compare two strings (case unsensitive)
*/

#include <stddef.h>

#include "my/strings.h"

int my_strcasecmp(const char *s1, const char *s2)
{
    size_t s1_len = my_strlen(s1);
    size_t s2_len = my_strlen(s2);
    size_t max_len = s2_len;

    if (s1_len > s2_len)
        max_len = s1_len;
    return my_strncasecmp(s1, s2, max_len);
}
