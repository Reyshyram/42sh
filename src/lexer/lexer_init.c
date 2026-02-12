/*
** EPITECH PROJECT, 2026
** lexer_init.c
** File description:
** Initialize the lexer
*/

#include "lexer.h"
#include "shell.h"

void lexer_init(lexer_t *lexer, char *line, shell_t *shell)
{
    lexer->line = line;
    lexer->pos = 0;
    lexer->shell = shell;
}
