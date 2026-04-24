/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/


#include "builtins.h"
#include "my/list.h"
#include "my/strings.h"
#include "shell.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "my/list.h"
#include "my/misc.h"

#include "ast.h"
#include "env.h"
#include "executer.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"
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

Test(execute_single_ls, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    our = execute_cmd(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_multiple_ls, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls;ls;ls;ls", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_ast(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_piped_ls, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls | ls > /tmp/ha| ls", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_pipe(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_redirected_ls, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > /tmp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_ast(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_null, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > /tmp/ha; foo < /tmp/ha", &shell);
    parser_init(&parser, &lexer);
    our = execute_ast(&shell, NULL);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_complex_command, hard)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls; ls > /tmp/ha && cat /tmp/ha; true || false; /bin/ls > /tmp/boo", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_ast(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_failed_left, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "thingymajib || ls", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_ast(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_success_left, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls && ls", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    our = execute_ast(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_redir_into_existing_file, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > src/main.c", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    our = execute_subshell(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_env, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("env"), &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    if (!node)
        return;
    our = execute_cmd(&shell, node);
    cr_assert_eq(our, SUCCESS);
}

Test(execute_wrong_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("ibuihbjj"), &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    if (!node)
        return;
    our = execute_cmd(&shell, node);
    cr_assert_eq(our, ERROR);
}

Test(execute_folder, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("/bin"), &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    if (!node)
        return;
    our = execute_cmd(&shell, node);
    cr_assert_eq(our, ERROR);
}

Test(execute_cat_on_no_perms_file, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("cat no_perms"), &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    if (!node)
        return;
    our = execute_cmd(&shell, node);
    cr_assert_eq(our, ERROR);
}

Test(execute_redirect_to_cat_on_no_perms_file, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("cat Makefile > tests/no_perms"), &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, true);
    if (!node)
        return;
    our = execute_redirect(&shell, node);
    cr_assert_eq(our, SUCCESS);
}
