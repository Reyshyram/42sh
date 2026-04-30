/*
** EPITECH PROJECT, 2026
** lexer_word.c
** File description:
** Handle a normal token
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "lexer.h"
#include "token.h"

/*************************************
* The handle_escape_sequence function handles the escape
* sequence for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
static bool handle_escape_sequence(lexer_t *lexer, struct lexer_reader *reader)
{
    char escape_char = '\0';

    lexer->pos++;
    if (!lexer->line[lexer->pos]) {
        lexer->error_message = "Unmatched '\\'.";
        return false;
    }
    escape_char = lexer->line[lexer->pos];
    lexer->pos++;
    if (escape_char == 'n')
        return lexer_append_str(lexer, reader, "\n", 1);
    if (escape_char == 't')
        return lexer_append_str(lexer, reader, "\t", 1);
    if (!lexer_append_str(lexer, reader, (char[2]) {escape_char, '\0'}, 1))
        return false;
    return true;
}

/*************************************
* The handle_double_quote function handles the double quote
* case for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
static bool handle_double_quote(lexer_t *lexer, struct lexer_reader *reader)
{
    reader->in_double_quotes = !reader->in_double_quotes;
    lexer->pos++;
    return true;
}

/*************************************
* The handle_single_quote function handles the single quote
* case for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
static bool handle_single_quote(lexer_t *lexer, struct lexer_reader *reader)
{
    size_t start = 0;

    lexer->pos++;
    start = lexer->pos;
    while (lexer->line[lexer->pos] && lexer->line[lexer->pos] != '\'')
        lexer->pos++;
    if (lexer->line[lexer->pos] != '\'') {
        lexer->error_message = "Unmatched '''.";
        return false;
    }
    if (!lexer_append_str(lexer, reader, &lexer->line[start],
            (ssize_t) lexer->pos - (ssize_t) start))
        return false;
    lexer->pos++;
    return true;
}

/*************************************
* The handle_current_token function handles the current token
* case for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false or the correct function
*************************************/
static bool handle_current_token(lexer_t *lexer, struct lexer_reader *reader)
{
    if (lexer->line[lexer->pos] == '$')
        return lexer_expand_variable(lexer, reader);
    if (lexer->line[lexer->pos] == '`')
        return lexer_expand_command_substitution(lexer, reader);
    if (!reader->in_double_quotes && lexer->line[lexer->pos] == '~')
        return lexer_expand_tilde(lexer, reader);
    if (lexer->line[lexer->pos] == '\\')
        return handle_escape_sequence(lexer, reader);
    if (lexer->line[lexer->pos] == '"')
        return handle_double_quote(lexer, reader);
    if (!reader->in_double_quotes && lexer->line[lexer->pos] == '\'')
        return handle_single_quote(lexer, reader);
    if (!lexer_append_current_char(lexer, reader))
        return false;
    return true;
}

/*************************************
* The lexer_word function reads the words written for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> either false or creates a token accordingly
*************************************/
token_t *lexer_word(lexer_t *lexer)
{
    struct lexer_reader reader;

    memset(&reader, 0, sizeof(struct lexer_reader));
    while (lexer->line[lexer->pos]) {
        if (!reader.in_double_quotes
            && lexer_is_word_separator(lexer->line[lexer->pos]))
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
        return create_token(TOKEN_WORD, strdup(""));
    return create_token(TOKEN_WORD, reader.buffer);
}
