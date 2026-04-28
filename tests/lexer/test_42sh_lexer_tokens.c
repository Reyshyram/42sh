/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/


#include "shell.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <limits.h>
#include "env.h"
#include <unistd.h>

#include "lexer.h"
#include "token.h"

Test(newline_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_NEWLINE;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\n"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(lparenthesis_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_LPARENTHESIS;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("(ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(rparenthesis_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_RPARENTHESIS;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup(")ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(semicolon_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_SEMICOLON;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup(";ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(logical_and_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_LOGICAL_AND;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    && ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(logical_or_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_LOGICAL_OR;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    || ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(pipe_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_PIPE;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    | ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(redirection_in_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_REDIRECT_IN;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    < ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(redirection_out_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_REDIRECT_OUT;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    > ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(redirect_append_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_REDIRECT_APPEND;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    >> ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(heredoc_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_HEREDOC;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    << ls"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(eof_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_EOF;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("    "), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}