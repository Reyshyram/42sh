/*
** EPITECH PROJECT, 2026
** lexer_word.c
** File description:
** Handle a normal token
*/

#include <stdlib.h>

#include "my/misc.h"
#include "my/strings.h"

#include "lexer.h"
#include "token.h"

struct reader {
    char *buffer;
    size_t buffer_size;
    bool in_double_quotes;
};

// Is it the start of a special token (so end of the word)
static bool is_special_token(lexer_t *lexer)
{
    char *str = &lexer->line[lexer->pos];

    if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '('
        || *str == ')' || *str == ';')
        return true;
    if ((str[0] == '&' && str[1] == '&') || (str[0] == '|' && str[1] == '|'))
        return true;
    return false;
}

static bool handle_escape_sequence(lexer_t *lexer, struct reader *reader)
{
    lexer->pos++;
    if (!lexer->line[lexer->pos])
        return false;
    reader->buffer = append_to_buffer(reader->buffer, &reader->buffer_size,
        (char[2]) {lexer->line[lexer->pos], '\0'}, 1);
    lexer->pos++;
    return true;
}

static bool handle_double_quote(lexer_t *lexer, struct reader *reader)
{
    reader->in_double_quotes = !reader->in_double_quotes;
    lexer->pos++;
    return true;
}

static bool handle_single_quote(lexer_t *lexer, struct reader *reader)
{
    size_t i = 0;

    lexer->pos++;
    while (lexer->line[lexer->pos] && lexer->line[lexer->pos] != '\'') {
        lexer->pos++;
        i++;
    }
    if (lexer->line[lexer->pos] == '\'') {
        append_to_buffer(reader->buffer, &reader->buffer_size,
            &lexer->line[lexer->pos - i], (int) i);
        lexer->pos++;
        return true;
    }
    lexer->error_message = "Unmatched '''.";
    return false;
}

static bool handle_current_token(lexer_t *lexer, struct reader *reader)
{
    if (lexer->line[lexer->pos] == '\\')
        return handle_escape_sequence(lexer, reader);
    if (lexer->line[lexer->pos] == '"')
        return handle_double_quote(lexer, reader);
    if (!reader->in_double_quotes && lexer->line[lexer->pos] == '\'')
        return handle_single_quote(lexer, reader);
    reader->buffer = append_to_buffer(reader->buffer, &reader->buffer_size,
        (char[2]) {lexer->line[lexer->pos], '\0'}, 1);
    lexer->pos++;
    return true;
}

token_t *lexer_word(lexer_t *lexer)
{
    struct reader reader;

    my_memset(&reader, 0, sizeof(struct reader));
    while (lexer->line[lexer->pos]) {
        if (!reader.in_double_quotes && is_special_token(lexer))
            break;
        if (!handle_current_token(lexer, &reader))
            break;
    }
    if (reader.in_double_quotes)
        lexer->error_message = "Unmatched '\"'.";
    if (lexer->error_message) {
        free(reader.buffer);
        return nullptr;
    }
    if (!reader.buffer)
        return nullptr;
    return create_token(TOKEN_WORD, reader.buffer);
}
