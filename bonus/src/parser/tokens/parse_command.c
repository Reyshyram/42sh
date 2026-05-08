/*
** EPITECH PROJECT, 2026
** parse_command.c
** File description:
** Parse a command
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my/list.h"
#include "my/misc.h"

#include "ast.h"
#include "parser.h"
#include "shell.h"
#include "token.h"

struct redirection_data {
    token_type_t type;
    char *file;
};

/*************************************
* The is_redirect_token function verifies if token is a redir 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> token_t *token, structure found in include/token.h
*   @return -> either false or token's type
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
* The parse_redirection_token function parses the token's redir for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @param -> linked_list_t **redirs, structure found
                        in include/list.h
*   @return -> a boolean, either false or parsing
*************************************/
static bool parse_redirection_token(parser_t *ps, linked_list_t **redirs)
{
    struct redirection_data *redir = malloc(sizeof(*redir));

    if (!redir)
        return false;
    redir->type = ps->current_token->type;
    if (!parser_next(ps) || ps->current_token->type != TOKEN_WORD) {
        parser_set_error(ps, "Missing name for redirect.");
        free(redir);
        return false;
    }
    redir->file = strdup(ps->current_token->value);
    if (!redir->file || !my_add_to_list_end(redirs, redir)) {
        free(redir->file);
        free(redir);
        return false;
    }
    return parser_next(ps);
}

/*************************************
* The parse_word_token function parses the word's token for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @param -> char ***argv, an array of strings
*   @param -> size_t *argc, size of argc
*   @return -> a boolean, either false or next parsing
*************************************/
static bool parse_word_token(parser_t *ps, char ***argv, size_t *argc)
{
    if (!parser_glob(ps, argv, argc))
        return false;
    return parser_next(ps);
}

/*************************************
* The free_redir_data function frees the redir's data for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> struct redirection_data *date, a structure
*************************************/
static void free_redir_data(struct redirection_data *data)
{
    if (!data)
        return;
    free(data->file);
    free(data);
}

/*************************************
* The apply_redirects function applies the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t *node, structure found in include/ast.h
*   @param -> char ***argv, an array of strings
*   @param -> size_t *argc, size of argc
*   @return -> current node
*************************************/
static ast_node_t *apply_redirects(ast_node_t *node, linked_list_t *redirs)
{
    struct redirection_data *data = nullptr;
    bool append = false;
    int fd = -1;

    for (linked_list_t *redir = redirs; redir; redir = redir->next) {
        data = redir->data;
        append = (data->type == TOKEN_REDIRECT_APPEND
            || data->type == TOKEN_HEREDOC);
        if (data->type == TOKEN_REDIRECT_OUT
            || data->type == TOKEN_REDIRECT_APPEND)
            fd = STDOUT_FILENO;
        else
            fd = STDIN_FILENO;
        node = ast_new_redirect(node, data->file, fd, append);
    }
    my_free_list(redirs, (void *) free_redir_data);
    return node;
}

/*************************************
* The parse_command_tokens function parses the command for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @param -> linked_list_t **redirs, a structure found in
                        include/list.h
*   @param -> char ***argv, an array of strings
*   @param -> size_t *argc, size of argc
*   @return -> a boolean, either true or false
*************************************/
static bool parse_command_tokens(parser_t *ps, linked_list_t **redirs,
    char ***argv, size_t *argc)
{
    bool redirect = false;

    while (ps->current_token
        && (ps->current_token->type == TOKEN_WORD
            || is_redirect_token(ps->current_token))) {
        redirect = is_redirect_token(ps->current_token);
        if (redirect && !parse_redirection_token(ps, redirs))
            return false;
        if (redirect)
            continue;
        if (!parse_word_token(ps, argv, argc))
            return false;
    }
    return true;
}

/*************************************
* The redirect_conflict function handles the redirs conflicts for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @param -> token_type_t type, a structure found in include/token.h
*   @param -> bool stdin_redirecter, a boolean
*   @param -> bool stdout_redirected, a boolean
*   @return -> a boolean, either true or parser_set_error
*************************************/
static bool redirect_conflict(parser_t *ps, token_type_t type,
    bool stdin_redirected, bool stdout_redirected)
{
    if ((type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND)
        && stdout_redirected) {
        parser_set_error(ps, "Ambiguous output redirect.");
        return true;
    }
    if ((type == TOKEN_REDIRECT_IN || type == TOKEN_HEREDOC)
        && stdin_redirected) {
        parser_set_error(ps, "Ambiguous input redirect.");
        return true;
    }
    return false;
}

/*************************************
* The check_redirects function verifies the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @param -> linked_list_t *redirs, a structure found
                        in include/list.h
*   @return -> a boolean, either true or false
*************************************/
static bool check_redirects(parser_t *ps, linked_list_t *redirs)
{
    struct redirection_data *data = nullptr;
    bool stdin_redirected = false;
    bool stdout_redirected = false;

    for (linked_list_t *redir = redirs; redir; redir = redir->next) {
        data = redir->data;
        if (redirect_conflict(ps, data->type, stdin_redirected,
                stdout_redirected))
            return false;
        if (data->type == TOKEN_REDIRECT_OUT
            || data->type == TOKEN_REDIRECT_APPEND)
            stdout_redirected = true;
        else
            stdin_redirected = true;
    }
    return true;
}

/*************************************
* The free_redirs_and_argv function frees the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> linked_list_t *redirs, a structure found
                        in include/list.h
*   @param -> char **argv, a string
*************************************/
static void *free_redirs_and_argv(linked_list_t *redirs, char **argv)
{
    my_free_list(redirs, (void *) free_redir_data);
    my_free_word_array(argv);
    return nullptr;
}

/*************************************
* The parse_command function frees the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *ps, structure found in include/parser.h
*   @return -> either nullptr or a node
*************************************/
ast_node_t *parse_command(parser_t *ps)
{
    size_t argc = 0;
    char **argv = nullptr;
    linked_list_t *redirs = nullptr;

    if (!parse_command_tokens(ps, &redirs, &argv, &argc))
        return free_redirs_and_argv(redirs, argv);
    if (argc == 0) {
        parser_set_error(ps, "Invalid null command.");
        if (!isatty(STDIN_FILENO))
            empty_stdin();
        return free_redirs_and_argv(redirs, argv);
    }
    if (!check_redirects(ps, redirs))
        return free_redirs_and_argv(redirs, argv);
    return apply_redirects(ast_new_cmd(argv, argc), redirs);
}
