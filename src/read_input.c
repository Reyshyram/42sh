/*
** EPITECH PROJECT, 2026
** read_stdin.c
** File description:
** read_stdin.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/colors.h"
#include "my/io.h"
#include "my/list.h"
#include "my/misc.h"
#include "my/strings.h"

#include "shell.h"

struct reader {
    char *buffer;
    char *line;
    ssize_t line_length;
    size_t buffer_size;
    size_t n;
    bool line_continuation;
};

static void print_prompt_prefix(int last_status)
{
    if (last_status != 0)
        my_printf(COLOR_RED "[%d] " COLOR_RESET, last_status);
}

static void show_prompt_with_curr_dir(linked_list_t *variables, char *curr_dir,
    int last_status)
{
    char *home_dir = nullptr;
    size_t home_dir_length = 0;

    home_dir = get_variable_value(variables, "home");
    if (!home_dir) {
        print_prompt_prefix(last_status);
        my_printf("%s\n> ", curr_dir);
        free(curr_dir);
        return;
    }
    home_dir_length = my_strlen(home_dir);
    if (!my_strncmp(curr_dir, home_dir, home_dir_length)
        && curr_dir[home_dir_length] == '/') {
        print_prompt_prefix(last_status);
        my_printf("~%s\n> ", curr_dir + home_dir_length);
    } else {
        print_prompt_prefix(last_status);
        my_printf("%s\n> ", curr_dir);
    }
    free(curr_dir);
}

static void show_prompt(linked_list_t *variables, bool interactive,
    bool line_continuation, int last_status)
{
    char *curr_dir = nullptr;

    if (!interactive)
        return;
    if (line_continuation) {
        my_putstr("? ");
        return;
    }
    curr_dir = getcwd(nullptr, 0);
    if (!curr_dir) {
        print_prompt_prefix(last_status);
        my_putstr("> ");
        return;
    }
    show_prompt_with_curr_dir(variables, curr_dir, last_status);
}

static char *handle_getline_error(char *line, char *buffer)
{
    if (line)
        free(line);
    return buffer;
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

char *read_input(linked_list_t *variables, bool interactive, int last_status)
{
    struct reader reader;

    my_memset(&reader, 0, sizeof(struct reader));
    while (true) {
        show_prompt(variables, interactive, reader.line_continuation,
            last_status);
        reader.line_length = getline(&reader.line, &reader.n, stdin);
        if (reader.line_length == -1)
            return handle_getline_error(reader.line, reader.buffer);
        reader.buffer = append_to_buffer(reader.buffer, &reader.buffer_size,
            reader.line, reader.line_length);
        if (!reader.buffer)
            return free(reader.line), nullptr;
        if (!handle_continuation(reader.buffer, &reader.buffer_size))
            break;
        reader.line_continuation = true;
    }
    free(reader.line);
    return reader.buffer;
}
