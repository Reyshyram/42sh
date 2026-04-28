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

Test(simple_space_sep, easy)
{
    shell_t shell;
    lexer_t lexer;
    bool our_env;
    bool not_our;
    char **env = __environ;
    char *av[2] = {"cd", ".."};

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("hi || hi"), &shell);
    our_env = lexer_is_word_separator(' ');
    not_our = true;
    cr_assert_eq(our_env, not_our);
}

Test(simple_semicolon_sep, easy)
{
    shell_t shell;
    lexer_t lexer;
    bool our_env;
    bool not_our;
    char **env = __environ;
    char *av[2] = {"cd", ".."};

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("hi || hi"), &shell);
    our_env = lexer_is_word_separator(';');
    not_our = true;
    cr_assert_eq(our_env, not_our);
}


Test(not_sep_char, easy)
{
    shell_t shell;
    lexer_t lexer;
    bool our_env;
    bool not_our;
    char **env = __environ;
    char *av[2] = {"cd", ".."};

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("hi || hi"), &shell);
    our_env = lexer_is_word_separator('d');
    not_our = false;
    cr_assert_eq(our_env, not_our);
}

Test(word_token, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    tok->value = strdup("ls");
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("hiiiii"), &shell);
    token = lexer_next_token(&lexer);
    cr_assert_eq(tok->type, token->type);
}

Test(unmatched_double_quote_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\" qsds"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(unmatched_single_quote_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\' qsds"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(matched_single_quote_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\' qsds\'"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(matched_double_quote_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\" ls\""), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(unmatched_escape_sequence_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\\ ls"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(matched_escape_sequence_t_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\\ lsqsdqsdn\\t"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(matched_escape_sequence_n_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("\\ lsqsdqsdn\\n"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(ampersand_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("& ls"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(wave_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("ls~  qsd"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(dollar_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("ls$qsd"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}

Test(last_value_lexer, easy)
{
    shell_t shell;
    lexer_t lexer;
    char **env = __environ;
    token_t *tok = malloc(sizeof(token_t));
    token_t *token;

    tok->type = TOKEN_WORD;
    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("ls$?sd"), &shell);
    token = lexer_next_token(&lexer);
    if (!token)
        return;
    cr_assert_eq(tok->type, token->type);
}
