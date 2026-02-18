/*
** EPITECH PROJECT, 2026
** parse_command.c
** File description:
** Parse a command
*/

#include <stddef.h>

#include "my/misc.h"
#include "my/strings.h"

#include "ast.h"
#include "parser.h"
#include "token.h"

ast_node_t *parse_command(parser_t *ps)
{
    size_t argc = 0;
    char **argv = nullptr;
    char **new_argv = nullptr;

    while (ps->current_token && ps->current_token->type == TOKEN_WORD) {
        new_argv = my_realloc(argv, sizeof(char *) * argc,
            sizeof(char *) * (argc + 2));
        if (!new_argv)
            return my_free_word_array(argv), nullptr;
        argv = new_argv;
        argv[argc] = my_strdup(ps->current_token->value);
        if (!argv[argc])
            return my_free_word_array(argv), nullptr;
        argv[argc + 1] = nullptr;
        argc++;
        if (!parser_next(ps))
            return my_free_word_array(argv), nullptr;
    }
    return ast_new_cmd(argv, argc);
}
