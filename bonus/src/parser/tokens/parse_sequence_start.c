/*
** EPITECH PROJECT, 2026
** parse_sequence_start.c
** File description:
** Parse the start of a sequence
*/

#include <string.h>

#include "ast.h"
#include "parser.h"
#include "token.h"

/*************************************
* The is_redirect_token function checks if the token is a redir for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> token_t *token, structure found in include/token.h
*   @return -> a boolean, either false or the token's type
*************************************/
static bool is_redirect_token(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_HEREDOC
        || token->type == TOKEN_REDIRECT_OUT
        || token->type == TOKEN_REDIRECT_APPEND;
}

/*************************************
* The parse_sequence_start function parses the beginning for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *parser, structure found in include/parser.h
*   @return -> either nullptr or parsing
*************************************/
ast_node_t *parse_sequence_start(parser_t *parser)
{
    token_t *token = parser->current_token;

    if (token && token->type == TOKEN_WORD && !strcmp(token->value, "repeat"))
        return parse_repeat(parser);
    if (token && (token->type == TOKEN_WORD || is_redirect_token(token)))
        return parse_command(parser);
    if (token && token->type == TOKEN_LPARENTHESIS) {
        return parse_subshell(parser);
    }
    parser_set_error(parser, "Invalid null command.");
    return nullptr;
}
