/*
** EPITECH PROJECT, 2026
** parser_utils
** File description:
** utilities for parser
*/

#include "ast.h"
#include "parser.h"
#include "token.h"

/*************************************
* The is_separator function verifies if the token
* contains a separator for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> token_t *token, structure found in include/token.h
*   @return_parameter -> a boolean, either true or the token's type
*************************************/

bool is_separator(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_NEWLINE || token->type == TOKEN_SEMICOLON;
}
/*************************************
* The skip_separator function skips the separators for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> parser_t *parser, structure found in include/parser.h
*   @return_parameter -> a boolean, either true or false
*************************************/

bool skip_separators(parser_t *parser)
{
    while (is_separator(parser->current_token))
        if (!parser_next(parser))
            return false;
    return true;
}
/*************************************
* The is_logical_token function checks if the token is logical for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> token_t *token, structure found in include/token.h
*   @return_parameter -> a boolean, either true or the token's type
*************************************/

bool is_logical_token(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_LOGICAL_AND || token->type == TOKEN_LOGICAL_OR
        || token->type == TOKEN_PIPE;
}
/*************************************
* The get_logical_type function retrieves the token's logical type for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> token_type_t type, structure found in include/token.h
*   @return_parameter -> the token's type
*************************************/

ast_type_t get_logical_type(token_type_t type)
{
    if (type == TOKEN_LOGICAL_AND)
        return AST_LOGICAL_AND;
    if (type == TOKEN_PIPE)
        return AST_PIPE;
    return AST_LOGICAL_OR;
}
/*************************************
* The is_sequence_end function checks the end of the sequence for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @entry_parameter -> token_t *token, structure found in include/token.h
*   @return_parameter -> the token's type
*************************************/

bool is_sequence_end(token_t *token)
{
    if (!token)
        return true;
    return token->type == TOKEN_EOF || token->type == TOKEN_RPARENTHESIS;
}
