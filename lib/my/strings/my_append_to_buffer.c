/*
** EPITECH PROJECT, 2026
** my_append_to_buffer.c
** File description:
** Append a string to a buffer
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *append_to_buffer(char *buffer, size_t *buffer_size, char *str,
    ssize_t str_length)
{
    char *new_buffer = realloc(buffer, *buffer_size + str_length + 1);

    if (!new_buffer)
        return nullptr;
    memcpy(new_buffer + *buffer_size, str, str_length);
    *buffer_size += str_length;
    new_buffer[*buffer_size] = '\0';
    return new_buffer;
}
