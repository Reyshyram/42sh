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
#include "parser.h"

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
    lexer_init(&lexer, strdup("ls ha"), &shell);
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
    lexer_init(&lexer, strdup("ls > /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("ls < /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("    a"), &shell);
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
    lexer_init(&lexer, strdup("ls;ls;ls;ls"), &shell);
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
    lexer_init(&lexer, strdup("ls > /tmp/ha; ls >> /tmp/ha; cat /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("ls )))"), &shell);
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
    lexer_init(&lexer, strdup("ls ||"), &shell);
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
    lexer_init(&lexer, strdup("ls >"), &shell);
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
    lexer_init(&lexer, strdup("(ls "), &shell);
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
    lexer_init(&lexer, strdup("ls ||       "), &shell);
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
    lexer_init(&lexer, strdup("(ls))"), &shell);
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
    lexer_init(&lexer, strdup(""), &shell);
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
    lexer_init(&lexer, strdup("ls > \"/tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("\"ls > /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("ls;ls; ls > /tmp/ha < /tmp/woah"), &shell);
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
    lexer_init(&lexer, strdup("ls;ls; ls > /tmp/ha < /tmp/woah"), &shell);
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
    lexer_init(&lexer, strdup("ls && ls || ls > /tmp/ha < /tmp/woah"), &shell);
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
    lexer_init(&lexer, strdup("ls > /tmp/a > /tmp/b > /tmp/c"), &shell);
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
    lexer_init(&lexer, strdup("ls < /tmp/a < /tmp/b < /tmp/c"), &shell);
    parser_init(&parser, &lexer);
    node = parse_command(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}

Test(parce_repeat_input, easy)
{
    shell_t shell;
    lexer_t lexer;
    parser_t parser;
    ast_node_t *node = nullptr;
    int not_our;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    lexer_init(&lexer, strdup("repeat"), &shell);
    parser_init(&parser, &lexer);
    node = parse_repeat(&parser);
    not_our = AST_SEQUENCE;
    if (!node)
        return;
    cr_assert_eq(node->type, not_our);
}
