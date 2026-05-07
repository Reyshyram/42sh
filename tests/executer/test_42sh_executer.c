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
#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include <time.h>
#include <unistd.h>
#include "my/misc.h"
#include "ast.h"
#include "executer.h"
#include "lexer.h"
#include "parser.h"

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
    lexer_init(&lexer, strdup("ls"), &shell);
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
    lexer_init(&lexer, strdup("ls;ls;ls;ls"), &shell);
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
    lexer_init(&lexer, strdup("ls | ls > /tmp/ha| ls"), &shell);
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
    lexer_init(&lexer, strdup("ls > /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("ls > /tmp/ha; foo < /tmp/ha"), &shell);
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
    lexer_init(&lexer, strdup("ls; ls > /tmp/ha && cat /tmp/ha; true || false; /bin/ls > /tmp/boo"), &shell);
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
    lexer_init(&lexer, strdup("thingymajib || ls"), &shell);
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
    lexer_init(&lexer, strdup("ls && ls"), &shell);
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
    lexer_init(&lexer, strdup("ls > src/main.c"), &shell);
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
