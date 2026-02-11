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
    if (buffer && *buffer)
        return buffer;
    free(buffer);
    return nullptr;
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

bool should_continue(const char *buffer, size_t buffer_size)
{
    if (buffer[buffer_size - 2] == '\\')
        return true;
    return false;
}

char *read_input(bool interactive)
{
    char *buffer = nullptr;
    char *line = nullptr;
    ssize_t line_length = 0;
    size_t buffer_size = 0;
    size_t n = 0;
    bool line_continuation = false;

    while (true) {
        show_prompt(interactive, line_continuation);
        line_length = getline(&line, &n, stdin);
        if (line_length == -1)
            return handle_getline_error(line, buffer);
        buffer = append_to_buffer(buffer, &buffer_size, line, line_length);
        if (!buffer) {
            free(line);
            return nullptr;
        }
        if (!should_continue(buffer, buffer_size))
            break;
        line_continuation = true;
    }
    free(line);
    return buffer;
}
