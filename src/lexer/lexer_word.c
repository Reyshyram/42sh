/*
** EPITECH PROJECT, 2026
** lexer_word.c
** File description:
** Handle a normal token
*/

#include <stddef.h>

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

token_t *lexer_word(lexer_t *lexer)
{
    struct reader reader;

    my_memset(&reader, 0, sizeof(struct reader));
    while (lexer->line[lexer->pos]) {
        if (!reader.in_double_quotes && is_special_token(lexer))
            break;
    }
    if (!reader.buffer)
        reader.buffer = my_strdup("");
    if (!reader.buffer)
        return nullptr;
    return create_token(TOKEN_WORD, reader.buffer);
}
