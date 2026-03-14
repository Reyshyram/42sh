/*
** EPITECH PROJECT, 2026
** parse_sequence_start.c
** File description:
** Parse the start of a sequence
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

static bool is_redirect_token(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_HEREDOC
        || token->type == TOKEN_REDIRECT_OUT
        || token->type == TOKEN_REDIRECT_APPEND;
}

ast_node_t *parse_sequence_start(parser_t *parser)
{
    if (parser->current_token
        && (parser->current_token->type == TOKEN_WORD
            || is_redirect_token(parser->current_token)))
        return parse_command(parser);
    if (parser->current_token
        && parser->current_token->type == TOKEN_LPARENTHESIS) {
        return parse_subshell(parser);
    }
    parser_set_error(parser, "Invalid null command.");
    return nullptr;
}
