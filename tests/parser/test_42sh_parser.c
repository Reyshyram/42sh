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

Test(simple_parcer_single_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls ha", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_CMD;
    cr_assert_eq(node->type, not_our);
}

Test(simple_parcer_output_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > tests/temp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_REDIRECT;
    cr_assert_eq(node->type, not_our);
}

Test(simple_parcer_input_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls < tests/temp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_REDIRECT;
    cr_assert_eq(node->type, not_our);
}

Test(simple_parcer_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "    a", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_CMD;
    cr_assert_eq(node->type, not_our);
}

Test(simple_parcer_list_commands, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls;ls;ls;ls", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_CMD;
    cr_assert_eq(node->type, not_our);
}

Test(long_parcer_list_commands, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > tests/temp/ha; ls >> tests/temp/ha; cat tests/temp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_REDIRECT;
    cr_assert_eq(node->type, not_our);
}

Test(parce_triple_right_parenthesis, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls )))", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = AST_REDIRECT;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_invalid_null_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls ||", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = AST_REDIRECT;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_invalid_redirect_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls >", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = AST_REDIRECT;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_missing_right_parenthesis_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "(ls ", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    parser_destroy(&parser);
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_eof_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls ||       ", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_too_many_right_parenthesis_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "(ls))", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_null_command, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_valid_separator_unmatched_double_quote, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > \"tests/temp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_invalid_separator_unmatched_double_quote, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "\"ls > tests/temp/ha", &shell);
    parser_init(&parser, &lexer);
    node = parser_parse(&parser, false);
    not_our = -1;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_sequence, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls;ls; ls > tests/temp/ha < tests/temp/woah", &shell);
    parser_init(&parser, &lexer);
    node = parse_sequence(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_subshell, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls;ls; ls > tests/temp/ha < tests/temp/woah", &shell);
    parser_init(&parser, &lexer);
    node = parse_subshell(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_logical_operator, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls && ls || ls > tests/temp/ha < tests/temp/woah", &shell);
    parser_init(&parser, &lexer);
    node = parse_subshell(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_ambiguous_output, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls > tests/temp/a > tests/temp/b > tests/temp/c", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_ambiguous_input, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, "ls < tests/temp/a < tests/temp/b < tests/temp/c", &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

