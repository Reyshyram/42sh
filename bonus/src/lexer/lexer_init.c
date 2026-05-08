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

void lexer_destroy(lexer_t *lexer)
{
    free(lexer->dup_line);
    lexer->dup_line = nullptr;
    lexer->line = nullptr;
}
