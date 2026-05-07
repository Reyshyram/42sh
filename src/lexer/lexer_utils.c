/*
** EPITECH PROJECT, 2026
** lexer_helpers.c
** File description:
** Utils for lexer
*/

#include <sys/types.h>

#include "my/strings.h"

#include "lexer.h"

/*************************************
* The lexer_set_alloc_error function gets the redir token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> a boolean, either true or false
*************************************/
bool lexer_set_alloc_error(lexer_t *lexer)
{
    lexer->error_message = "Couldn't allocate memory while lexing.";
    return false;
}

/*************************************
* The lexer_set_alloc_error function gets the redir token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @param -> char *str, a string
*   @param -> ssize_t str_length, the size of the string
*   @return -> a boolean, either false or another function
*************************************/
bool lexer_append_str(lexer_t *lexer, struct lexer_reader *reader, char *str,
    ssize_t str_length)
{
    reader->buffer = append_to_buffer(reader->buffer, &reader->buffer_size,
        str, str_length);
    if (!reader->buffer)
        return lexer_set_alloc_error(lexer);
    return true;
}

/*************************************
* The lexer_set_alloc_error function gets the redir token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
bool lexer_append_current_char(lexer_t *lexer, struct lexer_reader *reader)
{
    if (!lexer_append_str(lexer, reader,
            (char[2]) {lexer->line[lexer->pos], '\0'}, 1))
        return false;
    lexer->pos++;
    return true;
}
