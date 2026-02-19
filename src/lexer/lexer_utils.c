/*
** EPITECH PROJECT, 2026
** lexer_helpers.c
** File description:
** Utils for lexer
*/

#include <sys/types.h>

#include "my/strings.h"

#include "lexer.h"

bool lexer_set_alloc_error(lexer_t *lexer)
{
    lexer->error_message = "Couldn't allocate memory while lexing.";
    return false;
}

bool lexer_append_str(lexer_t *lexer, struct lexer_reader *reader, char *str,
    ssize_t str_length)
{
    reader->buffer = append_to_buffer(reader->buffer, &reader->buffer_size,
        str, str_length);
    if (!reader->buffer)
        return lexer_set_alloc_error(lexer);
    return true;
}

bool lexer_append_current_char(lexer_t *lexer, struct lexer_reader *reader)
{
    if (!lexer_append_str(lexer, reader,
            (char[2]) {lexer->line[lexer->pos], '\0'}, 1))
        return false;
    lexer->pos++;
    return true;
}
