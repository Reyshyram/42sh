/*
** EPITECH PROJECT, 2026
** parser_parse.c
** File description:
** Parse the tokens from the lexer
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

/*************************************
* The prepare_parser function prepares for the real parser function for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *ps, structure found in include/parser.h
*   @entry_parameter -> bool in_subshell, a boolean passed
*   @return_parameter -> a boolean, either true or false
*************************************/

static bool prepare_parser(parser_t *ps, bool in_subshell)
{
    if (!skip_separators(ps))
        return false;
    if (ps->current_token && ps->current_token->type == TOKEN_EOF)
        return false;
    if (!in_subshell && ps->current_token
        && ps->current_token->type == TOKEN_RPARENTHESIS) {
        parser_set_error(ps, "Too many )'s.");
        return false;
    }
    return true;
}
/*************************************
* The parser_parse function parses the arguments for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *ps, structure found in include/parser.h
*   @entry_parameter -> bool in_subshell, a boolean passed
*   @return_parameter -> either ast or nullptr
*************************************/

ast_node_t *parser_parse(parser_t *ps, bool in_subshell)
{
    ast_node_t *ast = nullptr;

    if (!prepare_parser(ps, in_subshell))
        return nullptr;
    ast = parse_sequence(ps);
    if (!ast)
        return nullptr;
    if (!skip_separators(ps))
        return ast_destroy(ast), nullptr;
    if (ps->current_token->type == TOKEN_EOF
        || (in_subshell && ps->current_token->type == TOKEN_RPARENTHESIS))
        return ast;
    if (ps->current_token && ps->current_token->type == TOKEN_RPARENTHESIS)
        parser_set_error(ps, "Too many )'s.");
    else
        parser_set_error(ps, "Invalid null command.");
    ast_destroy(ast);
    return nullptr;
}
