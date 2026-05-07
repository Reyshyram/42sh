/*
** EPITECH PROJECT, 2026
** lexer_expand_tilde.c
** File description:
** Expand tilde to home directory
*/

#include <string.h>
#include <sys/types.h>

#include "lexer.h"
#include "shell.h"

/*************************************
* The should_expand_tilde function should expand
* the tilde for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
static bool should_expand_tilde(lexer_t *lexer, struct lexer_reader *reader)
{
    if (reader->buffer_size != 0)
        return false;
    if (lexer->line[lexer->pos + 1] == '/'
        || lexer_is_word_separator(lexer->line[lexer->pos + 1]))
        return true;
    return false;
}

/*************************************
* The lexer_expand_tilde function expands the lexer's
* tilde for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> struct lexer_reader *reader, a structure reading the lexer
*   @return -> a boolean, either true or false
*************************************/
bool lexer_expand_tilde(lexer_t *lexer, struct lexer_reader *reader)
{
    char *home = nullptr;

    if (!should_expand_tilde(lexer, reader)) {
        lexer->pos++;
        return lexer_append_str(lexer, reader, "~", 1);
    }
    home = get_variable_value(lexer->shell->variables, "home");
    if (!home) {
        lexer->error_message = "No $home variable set.";
        return false;
    }
    if (!lexer_append_str(lexer, reader, home, (ssize_t) strlen(home)))
        return false;
    lexer->pos++;
    return true;
}
