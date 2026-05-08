/*
** EPITECH PROJECT, 2026
** lexer_next_token.c
** File description:
** Get the next token
*/

#include <string.h>

#include "lexer.h"
#include "token.h"

/*************************************
* The skip_spaces_and_tabs function skips all the spaces
* and tabs characters in the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*************************************/
static void skip_spaces_and_tabs(lexer_t *lexer)
{
    while (lexer->line[lexer->pos] == ' ' || lexer->line[lexer->pos] == '\t')
        lexer->pos++;
}

/*************************************
* The skip_comment function skips all the comments for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*************************************/
static void skip_comment(lexer_t *lexer)
{
    while (lexer->line[lexer->pos] && lexer->line[lexer->pos] != '\n')
        lexer->pos++;
}

/*************************************
* The get_logical_token function gets the logical token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> either nullptr or another function
*************************************/
static token_t *get_logical_token(lexer_t *lexer)
{
    if (!strncmp(&lexer->line[lexer->pos], "&&", 2))
        return lexer_logical_and(lexer);
    if (!strncmp(&lexer->line[lexer->pos], "||", 2))
        return lexer_logical_or(lexer);
    if (lexer->line[lexer->pos] == '|')
        return lexer_pipe(lexer);
    return nullptr;
}

/*************************************
* The get_redirection_token function gets the redir token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> either nullptr or another function
*************************************/
static token_t *get_redirection_token(lexer_t *lexer)
{
    if (!strncmp(&lexer->line[lexer->pos], ">>", 2))
        return lexer_redirect_append(lexer);
    if (!strncmp(&lexer->line[lexer->pos], "<<", 2))
        return lexer_heredoc(lexer);
    if (lexer->line[lexer->pos] == '>')
        return lexer_redirect_out(lexer);
    if (lexer->line[lexer->pos] == '<')
        return lexer_redirect_in(lexer);
    return nullptr;
}

/*************************************
* The return_token function returns the token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @param -> token_t *token, a struct found in include/token.h
*   @return -> the new token
*************************************/
static token_t *return_token(lexer_t *lexer, token_t *token)
{
    if (token) {
        lexer->is_first_token = false;
        lexer->previous_token_type = token->type;
    }
    return token;
}

/*************************************
* The lexer_next_token function gets the redir token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> lexer_t *lexer, a structure found in include/lexer.h
*   @return -> either nullptr or another function
*************************************/
token_t *lexer_next_token(lexer_t *lexer)
{
    token_t *token = nullptr;

    skip_spaces_and_tabs(lexer);
    if (lexer->line[lexer->pos] == '#')
        skip_comment(lexer);
    if (!lexer->line[lexer->pos])
        return return_token(lexer, create_token(TOKEN_EOF, nullptr));
    if (lexer->line[lexer->pos] == '\n')
        return return_token(lexer, lexer_newline(lexer));
    if (lexer->line[lexer->pos] == '(' || lexer->line[lexer->pos] == ')')
        return return_token(lexer, lexer_parenthesis(lexer));
    if (lexer->line[lexer->pos] == ';')
        return return_token(lexer, lexer_semicolon(lexer));
    token = get_logical_token(lexer);
    if (token)
        return return_token(lexer, token);
    token = get_redirection_token(lexer);
    if (token)
        return return_token(lexer, token);
    return return_token(lexer, lexer_word(lexer));
}
