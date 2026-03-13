/*
** EPITECH PROJECT, 2026
** parse_sequence_start.c
** File description:
** Parse the start of a sequence
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

ast_node_t *parse_sequence_start(parser_t *parser)
{
    if (parser->current_token && parser->current_token->type == TOKEN_WORD)
        return parse_command(parser);
    if (parser->current_token
        && parser->current_token->type == TOKEN_LPARENTHESIS) {
        return parse_subshell(parser);
    }
    parser_set_error(parser, "Invalid null command.");
    return nullptr;
}
