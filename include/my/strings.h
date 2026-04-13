/*
** EPITECH PROJECT, 2025
** my/strings.h
** File description:
** Functions related to strings
*/

#ifndef MY_STRINGS_H
// clang-format off
    #define MY_STRINGS_H

    #include <stddef.h>
    #include <sys/types.h>
// clang-format on

int my_getindex(char c, const char *str);

bool my_str_isnum(const char *str);
bool my_isnumber(char c);

bool my_is_char_in_str(const char *str, char c);

char *append_to_buffer(char *buffer, size_t *buffer_size, char *str,
    ssize_t str_length);

#endif /* MY_STRINGS_H */
