/*
** EPITECH PROJECT, 2025
** my_strtok_r.c
** File description:
** Reproduce the behavior of strtok_r
*/

#include "my/strings.h"

static char *find_token(char *tmp, const char *delim, char **saveptr)
{
    char *start = nullptr;

    while (*tmp && my_is_char_in_str(delim, *tmp))
        tmp++;
    if (!(*tmp)) {
        *saveptr = nullptr;
        return nullptr;
    }
    start = tmp;
    while (*tmp && !my_is_char_in_str(delim, *tmp))
        tmp++;
    if (*tmp) {
        *tmp = '\0';
        *saveptr = tmp + 1;
    } else
        *saveptr = nullptr;
    return start;
}

char *my_strtok_r(char *str, const char *delim, char **saveptr)
{
    char *tmp = nullptr;

    if (!delim || (!str && !saveptr))
        return nullptr;
    if (str)
        tmp = str;
    else {
        if (!(*saveptr))
            return nullptr;
        tmp = *saveptr;
    }
    return find_token(tmp, delim, saveptr);
}
