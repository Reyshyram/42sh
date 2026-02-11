/*
** EPITECH PROJECT, 2026
** read_stdin.c
** File description:
** read_stdin.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "my/io.h"
#include "my/misc.h"
#include "shell.h"

struct reader {
    char *buffer;
    char *line;
    ssize_t line_length;
    size_t buffer_size;
    size_t n;
    bool line_continuation;
};

static void show_prompt(bool interactive, bool line_continuation)
{
    if (!interactive)
        return;
    if (line_continuation)
        my_putstr("? ");
    else
        my_putstr("> ");
}

static char *handle_getline_error(char *line, char *buffer)
{
    if (line)
        free(line);
    return buffer;
}

static char *append_to_buffer(char *buffer, size_t *buffer_size, char *line,
    ssize_t line_length)
{
    char *new_buffer =
        my_realloc(buffer, *buffer_size + 1, *buffer_size + line_length + 1);

    if (!new_buffer)
        return nullptr;
    my_memcpy(new_buffer + *buffer_size, line, line_length);
    *buffer_size += line_length;
    new_buffer[*buffer_size] = '\0';
    return new_buffer;
}

// Count the number of backslahes from the end to know if one is not escaped
static bool should_continue(const char *buffer, const size_t *buffer_size)
{
    size_t i = *buffer_size - 1;
    size_t nb_backlslah = 0;

    if (*buffer_size == 0)
        return false;
    if (buffer[i] == '\n') {
        if (i == 0)
            return false;
        i--;
    }
    while (true) {
        if (buffer[i] != '\\')
            break;
        nb_backlslah++;
        if (i == 0)
            break;
        i--;
    }
    return (nb_backlslah % 2) == 1;
}

// Strip backslahs and newline from end of input to make it a single line
static bool handle_continuation(char *buffer, size_t *buffer_size)
{
    if (!should_continue(buffer, buffer_size))
        return false;
    if (*buffer_size >= 2 && buffer[*buffer_size - 1] == '\n')
        *buffer_size -= 2;
    else if (*buffer_size >= 1)
        *buffer_size -= 1;
    buffer[*buffer_size] = '\0';
    return true;
}

char *read_input(bool interactive)
{
    struct reader reader;

    my_memset(&reader, 0, sizeof(struct reader));
    while (true) {
        show_prompt(interactive, reader.line_continuation);
        reader.line_length = getline(&reader.line, &reader.n, stdin);
        if (reader.line_length == -1)
            return handle_getline_error(reader.line, reader.buffer);
        reader.buffer = append_to_buffer(reader.buffer, &reader.buffer_size,
            reader.line, reader.line_length);
        if (!reader.buffer) {
            free(reader.line);
            return nullptr;
        }
        if (!handle_continuation(reader.buffer, &reader.buffer_size))
            break;
        reader.line_continuation = true;
    }
    free(reader.line);
    return reader.buffer;
}
