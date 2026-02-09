/*
** EPITECH PROJECT, 2025
** my_strncasecmp
** File description:
** Compare the first n characters of two strings (case insensitive)
*/

#include <stddef.h>

#include <my/strings.h>

int my_strncasecmp(const char *s1, const char *s2, size_t n)
{
    unsigned char c1;
    unsigned char c2;

    if (s1 != nullptr && s2 == nullptr)
        return 1;
    if (s1 == nullptr && s2 != nullptr)
        return -1;
    if (s1 == nullptr && s2 == nullptr)
        return 0;
    for (size_t i = 0; i < n; i++) {
        c1 = (unsigned char) my_isupper(s1[i]) ? s1[i] + 32 : s1[i];
        c2 = (unsigned char) my_isupper(s2[i]) ? s2[i] + 32 : s2[i];
        if (c1 == '\0' && c2 == '\0')
            return 0;
        if (c1 > c2)
            return 1;
        if (c2 > c1)
            return -1;
    }
    return 0;
}
