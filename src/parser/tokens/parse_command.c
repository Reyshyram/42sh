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

static bool is_redirect_token(token_t *token)
{
    if (!token)
        return false;
    return token->type == TOKEN_REDIRECT_IN || token->type == TOKEN_HEREDOC
        || token->type == TOKEN_REDIRECT_OUT
        || token->type == TOKEN_REDIRECT_APPEND;
}

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

static bool parse_word_token(parser_t *ps, char ***argv, size_t *argc)
{
    char **new_argv = realloc(*argv, sizeof(char *) * (*argc + 2));

    if (!new_argv)
        return false;
    *argv = new_argv;
    (*argv)[*argc] = strdup(ps->current_token->value);
    if (!(*argv)[*argc])
        return false;
    (*argv)[*argc + 1] = nullptr;
    (*argc)++;
    return parser_next(ps);
}

static void free_redir_data(struct redirection_data *data)
{
    if (!data)
        return;
    free(data->file);
    free(data);
}

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

static void *free_redirs_and_argv(linked_list_t *redirs, char **argv)
{
    my_free_list(redirs, (void *) free_redir_data);
    my_free_word_array(argv);
    return nullptr;
}

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
