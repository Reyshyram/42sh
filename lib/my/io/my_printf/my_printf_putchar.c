/*
** EPITECH PROJECT, 2025
** my_printf_putchar
** File description:
** Print a character for printf
*/

#include "my/printf/types.h"
#include <unistd.h>

void my_printf_putchar(printf_buffer_t *buffer, char c)
{
    if (buffer->pos >= buffer->max_size) {
        if (buffer->fd < 0)
            return;
        write(buffer->fd, buffer->buffer, buffer->pos);
        buffer->pos = 0;
    }
    buffer->buffer[buffer->pos] = c;
    buffer->pos++;
    buffer->length++;
}
