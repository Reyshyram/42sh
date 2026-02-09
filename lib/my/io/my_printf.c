/*
** EPITECH PROJECT, 2025
** my_printf
** File description:
** Recreation of printf
*/

#include <errno.h>
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>

#include "my/io.h"
#include "my/printf/flags.h"
#include "my/printf/io.h"
#include "my/printf/types.h"
#include "my/strings.h"

static void parse(printf_buffer_t *buffer, const char *format, va_list args)
{
    while (*format) {
        if (*format == '%') {
            format++;
            format = my_printf_handle_flags(buffer, format, args);
        } else
            my_printf_putchar(buffer, *format);
        format++;
    }
}

static void print_buffer(printf_buffer_t *buffer)
{
    if (buffer->pos > 0) {
        write(buffer->fd, buffer->buffer, buffer->pos);
        buffer->pos = 0;
    }
}

int my_printf(const char *format, ...)
{
    va_list args;
    char write_buffer[PRINTF_BUFFER_SIZE];
    printf_buffer_t buffer = {write_buffer, STDOUT_FILENO, PRINTF_BUFFER_SIZE,
        0, 0};

    va_start(args, format);
    parse(&buffer, format, args);
    va_end(args);
    print_buffer(&buffer);
    if (buffer.length > INT_MAX) {
        errno = EOVERFLOW;
        return -1;
    }
    return (int) buffer.length;
}

int my_dprintf(int fd, const char *format, ...)
{
    va_list args;
    char write_buffer[PRINTF_BUFFER_SIZE];
    printf_buffer_t buffer = {write_buffer, fd, PRINTF_BUFFER_SIZE, 0, 0};

    va_start(args, format);
    parse(&buffer, format, args);
    va_end(args);
    print_buffer(&buffer);
    if (buffer.length > INT_MAX) {
        errno = EOVERFLOW;
        return -1;
    }
    return (int) buffer.length;
}

int my_sprintf(char *str, const char *format, ...)
{
    va_list args;
    char write_buffer[PRINTF_BUFFER_SIZE];
    printf_buffer_t buffer = {write_buffer, -1, PRINTF_BUFFER_SIZE, 0, 0};

    va_start(args, format);
    parse(&buffer, format, args);
    va_end(args);
    if (buffer.length > INT_MAX) {
        errno = EOVERFLOW;
        return -1;
    }
    my_strncpy(str, buffer.buffer, buffer.length);
    return (int) buffer.length;
}

int my_asprintf(char **str, const char *format, ...)
{
    va_list args;
    char write_buffer[PRINTF_BUFFER_SIZE];
    printf_buffer_t buffer = {write_buffer, -1, PRINTF_BUFFER_SIZE, 0, 0};

    va_start(args, format);
    parse(&buffer, format, args);
    va_end(args);
    if (buffer.length > INT_MAX) {
        errno = EOVERFLOW;
        return -1;
    }
    *str = my_strndup(buffer.buffer, buffer.length);
    return (int) buffer.length;
}
