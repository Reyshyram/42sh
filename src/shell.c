/*
** EPITECH PROJECT, 2026
** shell.c
** File description:
** shell.c
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my/list.h"
#include "my/misc.h"

#include "ast.h"
#include "env.h"
#include "executer.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"

static void handle_sigint(int signal)
{
    (void) signal;
    write(STDOUT_FILENO, "\n", 1);
}

static bool init_variables(shell_t *shell)
{
    char *home = get_variable_value(shell->env, "HOME");
    char *term = nullptr;
    char *cwd = getcwd(nullptr, 0);

    if (!cwd)
        return false;
    if (home && !set_variable(&shell->variables, "home", home))
        return false;
    term = get_variable_value(shell->env, "TERM");
    if (term && !set_variable(&shell->variables, "term", term))
        return false;
    if (!set_variable(&shell->variables, "cwd", cwd))
        return false;
    free(cwd);
    return true;
}

static bool init_shell(shell_t *shell, char **env)
{
    memset(shell, 0, sizeof(*shell));
    shell->interactive = isatty(STDIN_FILENO);
    shell->env = env_to_list(env);
    if (!shell->env && *env)
        return false;
    if (shell->interactive && signal(SIGINT, handle_sigint) == SIG_ERR)
        return false;
    return init_variables(shell);
}

static void shell_destroy(shell_t *shell)
{
    my_free_list(shell->env, (void *) free_variable);
    my_free_list(shell->variables, (void *) free_variable);
    my_free_list(shell->aliases, (void *) free_variable);
}

static void show_error_message(parser_t *parser)
{
    if (parser->error_message_prefix) {
        fprintf(stderr, "%s: %s\n", parser->error_message_prefix,
            parser->error_message);
        free(parser->error_message_prefix);
    } else
        fprintf(stderr, "%s\n", parser->error_message);
}

static bool parse_ast(ast_node_t **ast, parser_t *parser)
{
    *ast = parser_parse(parser, false);
    if (!*ast) {
        if (!parser->error_message)
            return true;
        show_error_message(parser);
        return false;
    }
    return true;
}

static bool handle_parsing(ast_node_t **ast, parser_t *parser)
{
    if (!parse_ast(ast, parser)) {
        if (!isatty(STDIN_FILENO))
            empty_stdin();
        return false;
    }
    return true;
}

static int destroy_parser_and_lexer(parser_t *parser, lexer_t *lexer)
{
    parser_destroy(parser);
    lexer_destroy(lexer);
    return ERROR;
}

int handle_input(shell_t *shell, char *line)
{
    parser_t parser;
    lexer_t lexer;
    ast_node_t *ast = nullptr;
    int status = 0;

    lexer_init(&lexer, line, shell);
    parser_init(&parser, &lexer);
    if (parser.error_message) {
        show_error_message(&parser);
        return destroy_parser_and_lexer(&parser, &lexer);
    }
    if (!handle_parsing(&ast, &parser))
        return destroy_parser_and_lexer(&parser, &lexer);
    destroy_parser_and_lexer(&parser, &lexer);
    status = execute_ast(shell, ast);
    ast_destroy(ast);
    return status;
}

int shell_run(char **env)
{
    shell_t sh;
    char *line = nullptr;

    if (!init_shell(&sh, env)) {
        fprintf(stderr, "memory: couldn't allocate memory for the shell\n");
        return ERROR;
    }
    while (true) {
        line = read_input(sh.variables, sh.interactive, sh.last_status);
        if (!line)
            break;
        sh.last_status = handle_input(&sh, line);
        free(line);
        if (sh.should_exit)
            break;
    }
    if (sh.interactive)
        printf("exit\n");
    shell_destroy(&sh);
    return sh.last_status;
}
