/*
** EPITECH PROJECT, 2026
** lexer_expand_command_substitution.c
** File description:
** Expand command substitution
*/

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "executer.h"
#include "lexer.h"

static bool append_command_output(lexer_t *lexer, struct lexer_reader *reader,
    char *command)
{
    char *output = execute_command_substitution(lexer->shell, command);

    if (!output)
        return lexer_set_alloc_error(lexer);
    if (!lexer_append_str(lexer, reader, output, (ssize_t) strlen(output))) {
        free(output);
        return false;
    }
    free(output);
    return true;
}

bool lexer_expand_command_substitution(lexer_t *lexer,
    struct lexer_reader *reader)
{
    size_t cmd_start = lexer->pos + 1;
    char *cmd = nullptr;
    bool success = false;

    lexer->pos++;
    while (lexer->line[lexer->pos] && lexer->line[lexer->pos] != '`')
        lexer->pos++;
    if (lexer->line[lexer->pos] != '`') {
        lexer->error_message = "Unmatched '`'.";
        return false;
    }
    cmd = strndup(lexer->line + cmd_start, lexer->pos - cmd_start);
    if (!cmd)
        return lexer_set_alloc_error(lexer);
    success = append_command_output(lexer, reader, cmd);
    free(cmd);
    if (!success)
        return false;
    lexer->pos++;
    return true;
}
