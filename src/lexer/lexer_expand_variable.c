/*
** EPITECH PROJECT, 2026
** lexer_expand_variable.c
** File description:
** Expand variable to its value
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "my/strings.h"

#include "lexer.h"
#include "shell.h"

static bool is_valid_variable_char(char c)
{
    return isupper(c) || islower(c) || my_isnumber(c) || c == '_';
}

static ssize_t get_variable_name_len(lexer_t *lexer)
{
    ssize_t i = 0;
    const char *line = &lexer->line[lexer->pos + 1];

    if (!is_valid_variable_char(line[0])
        && !(line[0] == '\n' || line[0] == '\0')) {
        lexer->error_message = "Illegal variable name.";
        return -1;
    }
    while (line[i] && is_valid_variable_char(line[i]))
        i++;
    return i;
}

static char *get_correct_variable_value(lexer_t *lexer, char *name)
{
    char *value = get_variable_value(lexer->shell->variables, name);

    if (value)
        return value;
    return get_variable_value(lexer->shell->env, name);
}

static bool append_last_status(lexer_t *lexer, struct lexer_reader *reader)
{
    char *last_status = nullptr;

    asprintf(&last_status, "%d", lexer->shell->last_status);
    if (!last_status)
        return lexer_set_alloc_error(lexer);
    if (!lexer_append_str(lexer, reader, last_status,
            (ssize_t) strlen(last_status))) {
        free(last_status);
        return false;
    }
    free(last_status);
    lexer->pos++;
    return true;
}

static bool append_variable_value(lexer_t *lexer, struct lexer_reader *reader,
    char *name, char *value)
{
    if (!value) {
        lexer->error_message_prefix = strdup(name);
        lexer->error_message = "Undefined variable.";
        free(name);
        return false;
    }
    return lexer_append_str(lexer, reader, value, (ssize_t) strlen(value));
}

static bool append_dollar(lexer_t *lexer, struct lexer_reader *reader)
{
    lexer->pos++;
    return lexer_append_str(lexer, reader, "$", 1);
}

bool lexer_expand_variable(lexer_t *lexer, struct lexer_reader *reader)
{
    ssize_t name_length = get_variable_name_len(lexer);
    char *name = nullptr;
    char *value = nullptr;

    if (name_length == -1)
        return false;
    lexer->pos++;
    if (lexer->line[lexer->pos] == '?')
        return append_last_status(lexer, reader);
    if (name_length == 0)
        return append_dollar(lexer, reader);
    name = strndup(&lexer->line[lexer->pos], name_length);
    if (!name)
        return lexer_set_alloc_error(lexer);
    value = get_correct_variable_value(lexer, name);
    if (!append_variable_value(lexer, reader, name, value))
        return false;
    free(name);
    lexer->pos += name_length;
    return true;
}
