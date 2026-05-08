/*
** EPITECH PROJECT, 2026
** lexer_expand_alias.c
** File description:
** Expand an alias
*/

#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "shell.h"
#include "token.h"

static bool should_expand_alias(lexer_t *lexer)
{
    if (lexer->is_first_token)
        return true;
    return lexer->previous_token_type != TOKEN_WORD;
}

static bool replace_word(lexer_t *lexer, size_t start, size_t end, char *alias)
{
    size_t line_length = strlen(lexer->line);
    size_t alias_length = strlen(alias);
    size_t after_alias_length = line_length - end;
    char *new_line = malloc(start + alias_length + after_alias_length + 1);

    if (!new_line)
        return lexer_set_alloc_error(lexer);
    memcpy(new_line, lexer->line, start);
    memcpy(new_line + start, alias, alias_length);
    memcpy(new_line + start + alias_length, lexer->line + end,
        after_alias_length);
    new_line[start + alias_length + after_alias_length] = '\0';
    free(lexer->dup_line);
    lexer->dup_line = new_line;
    lexer->line = new_line;
    lexer->pos = start;
    return true;
}

bool lexer_expand_alias(lexer_t *lexer, struct lexer_reader *reader,
    size_t start)
{
    variable_t *alias = nullptr;

    if (!should_expand_alias(lexer) || !reader->buffer)
        return true;
    for (size_t expansion_count = 0; reader->buffer; expansion_count++) {
        alias = get_variable(lexer->shell->aliases, reader->buffer);
        if (!alias)
            return true;
        if (expansion_count >= TCSH_MAX_ALIAS_SUBSTITUTIONS) {
            lexer->error_message = "Alias loop.";
            return false;
        }
        if (!replace_word(lexer, start, lexer->pos, alias->value))
            return false;
        free(reader->buffer);
        memset(reader, 0, sizeof(*reader));
        if (!lexer_read_word(lexer, reader))
            return false;
    }
    return true;
}
