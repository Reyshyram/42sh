/*
** EPITECH PROJECT, 2026
** parse_repeat.c
** File description:
** Parse a repeat instruction
*/

#include <stdlib.h>
#include <string.h>

#include "my/strings.h"

#include "ast.h"
#include "parser.h"
#include "token.h"

static void *error_too_few_arguments(parser_t *ps)
{
    ps->error_message = "repeat: Too few arguments.";
    return nullptr;
}

static void *error_memory(parser_t *ps)
{
    parser_set_error(ps, "repeat: Memory error.");
    return nullptr;
}

static ast_node_t *parse_repeat_ast(parser_t *ps, int count)
{
    ast_node_t *node = parse_sequence_start(ps);

    if (!node)
        return error_too_few_arguments(ps);
    return ast_new_repeat(node, count);
}

ast_node_t *parse_repeat(parser_t *ps)
{
    int count = 0;
    char *count_str = nullptr;

    if (!parser_next(ps) || ps->current_token->type != TOKEN_WORD)
        return error_too_few_arguments(ps);
    count_str = strdup(ps->current_token->value);
    if (!count_str)
        return error_memory(ps);
    if (!parser_next(ps)) {
        free(count_str);
        return error_too_few_arguments(ps);
    }
    if (!my_str_isnum(count_str)) {
        parser_set_error(ps, "repeat: Badly formed number.");
        free(count_str);
        return nullptr;
    }
    count = atoi(count_str);
    free(count_str);
    return parse_repeat_ast(ps, count);
}
