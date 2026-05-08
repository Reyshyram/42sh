/*
** EPITECH PROJECT, 2026
** lexer_init.c
** File description:
** Initialize the lexer
*/

#include <stdlib.h>

#include "lexer.h"
#include "shell.h"
#include "token.h"

/*************************************
* The lexer_init function initialises the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> char *line, the string of the line
*   @param -> shell_t *shell, a struct found in include/shell.h
*************************************/
void lexer_init(lexer_t *lexer, char *line, shell_t *shell)
{
    lexer->line = line;
    lexer->dup_line = nullptr;
    lexer->pos = 0;
    lexer->is_first_token = true;
    lexer->previous_token_type = TOKEN_EOF;
    lexer->shell = shell;
    lexer->error_message = nullptr;
    lexer->error_message_prefix = nullptr;
}

/*************************************
* The lexer_destroy function destroys the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*************************************/
void lexer_destroy(lexer_t *lexer)
{
    free(lexer->dup_line);
    lexer->dup_line = nullptr;
    lexer->line = nullptr;
}
