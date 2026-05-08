/*
** EPITECH PROJECT, 2026
** read_stdin.c
** File description:
** read_stdin.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/colors.h"
#include "my/list.h"
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

/*************************************
* The print_prompt_prefix function print the prefix for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int last_status, an integer
*************************************/
static void print_prompt_prefix(int last_status)
{
    if (last_status != 0)
        printf(COLOR_RED "[%d] " COLOR_RESET, last_status);
}

/*************************************
* The show_prompt_with_current_dir function shows the prompt
* with the current directory for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> linked_list_t *variables, a struct found in include/my/list.h
*   @param -> char *current_dir, a string of the current directory
*   @param -> int last_status, an integer
*************************************/
static void show_prompt_with_curr_dir(linked_list_t *variables, char *curr_dir,
    int last_status)
{
    char *home_dir = nullptr;
    size_t home_dir_length = 0;

    home_dir = get_variable_value(variables, "home");
    if (!home_dir) {
        print_prompt_prefix(last_status);
        printf("%s\n> ", curr_dir);
        free(curr_dir);
        return;
    }
    home_dir_length = strlen(home_dir);
    if (!strncmp(curr_dir, home_dir, home_dir_length)
        && (curr_dir[home_dir_length] == '/' || !curr_dir[home_dir_length])) {
        print_prompt_prefix(last_status);
        printf("~%s\n> ", curr_dir + home_dir_length);
    } else {
        print_prompt_prefix(last_status);
        printf("%s\n> ", curr_dir);
    }
    free(curr_dir);
}

/*************************************
* The execute_precmd function executes the precmd for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> char *precmd, a string of the precmd
*************************************/
static void execute_precmd(shell_t *shell, char *precmd)
{
    char *copy = strdup(precmd);

    if (!copy)
        return;
    handle_input(shell, copy);
    printf("> ");
    free(copy);
}

/*************************************
* The show_prompt function shows the prompt for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/my/shell.h
*   @param -> bool interactive, a boolean
*   @param -> bool line_continuation, a boolean
*   @param -> int last_status, an integer
*************************************/
static void show_prompt(shell_t *shell, bool interactive,
    bool line_continuation, int last_status)
{
    char *curr_dir = nullptr;
    char *precmd = nullptr;

    if (!interactive || line_continuation) {
        if (line_continuation)
            printf("? ");
        return;
    }
    precmd = get_variable_value(shell->aliases, "precmd");
    if (precmd) {
        execute_precmd(shell, precmd);
        return;
    }
    curr_dir = getcwd(nullptr, 0);
    if (!curr_dir) {
        print_prompt_prefix(last_status);
        printf("> ");
        return;
    }
    show_prompt_with_curr_dir(shell->variables, curr_dir, last_status);
}

/*************************************
* The handle_getline_error function handles the getline errors for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *line, a string of the line
*   @param -> char *buffer, a string of the buffer
*   @return -> a string of the buffer
*************************************/
static char *handle_getline_error(char *line, char *buffer)
{
    if (line)
        free(line);
    return buffer;
}

/*************************************
* The should_continue function checks if the process should continue for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
* /!\ Count the number of backslashes from the end to
* /!\ know if one is not escaped.
*
*   @param -> const char *buffer, a string of the buffer
*   @param -> const size_t *buffer_size, the length of the buffer
*   @return -> a boolean, either true or false
*************************************/
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

/*************************************
* The handle_continuation function handles the continuation for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
* /!\ Strip baskslashes and newline from end of input to make it a single line.
*
*   @param -> char *buffer, a string of the buffer
*   @param -> size_t *buffer_size, the length of the buffer
*   @return -> a boolean, either true or false
*************************************/
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

/*************************************
* The read_input function reads the input for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> bool interactive, a boolean
*   @param -> int last_status, an integer
*   @return -> a string of the input
*************************************/
char *read_input(shell_t *shell, bool interactive, int last_status)
{
    struct reader reader;

    memset(&reader, 0, sizeof(struct reader));
    while (true) {
        show_prompt(shell, interactive, reader.line_continuation, last_status);
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
    if (reader.buffer)
        shell->eof_count = 0;
    return reader.buffer;
}
