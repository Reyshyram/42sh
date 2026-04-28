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
#include <stdlib.h>
#include "env.h"
#include <signal.h>
#include <unistd.h>

#include "lexer.h"
#include "token.h"


static void handle_sigint([[maybe_unused]] int signal)
{
    write(STDOUT_FILENO, "\n", 1);
}

static bool init_variables(shell_t *shell)
{
    char *home = get_variable_value(shell->env, "HOME");
    char *cwd = getcwd(nullptr, 0);

    if (!cwd)
        return false;
    if (home && !set_variable(&shell->variables, "home", home))
        return false;
    if (!set_variable(&shell->variables, "cwd", cwd))
        return false;
    free(cwd);
    return true;
}

static bool init_shell(shell_t *shell, char **env)
{
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->should_exit = false;
    shell->is_subprocess = false;
    shell->is_out_redirected = false;
    shell->is_in_redirected = false;
    shell->env = env_to_list(env);
    shell->variables = nullptr;
    if (!shell->env && *env)
        return false;
    if (shell->interactive && signal(SIGINT, handle_sigint) == SIG_ERR)
        return false;
    return init_variables(shell);
}

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