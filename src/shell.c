/*
** EPITECH PROJECT, 2026
** shell.c
** File description:
** shell.c
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#include "my/io.h"
#include "my/list.h"
#include "my/misc.h"

#include "ast.h"
#include "env.h"
#include "executer.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"

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
    shell->should_exit_status = 0;
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

static void shell_destroy(shell_t *shell)
{
    my_free_list(shell->env, (void *) free_variable);
    my_free_list(shell->variables, (void *) free_variable);
}

static void show_error_message(parser_t *parser)
{
    if (parser->error_message_prefix) {
        my_dprintf(STDERR_FILENO, "%s: %s\n", parser->error_message_prefix,
            parser->error_message);
        free(parser->error_message_prefix);
    } else
        my_dprintf(STDERR_FILENO, "%s\n", parser->error_message);
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
        parser_destroy(&parser);
        return ERROR;
    }
    if (!parse_ast(&ast, &parser)) {
        parser_destroy(&parser);
        return ERROR;
    }
    parser_destroy(&parser);
    status = execute_ast(shell, ast);
    ast_destroy(ast);
    return status;
}

int shell_run(char **env)
{
    shell_t sh;
    char *line = nullptr;

    if (!init_shell(&sh, env)) {
        my_puterr("memory: couldn't allocate memory for the shell\n");
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
        my_putstr("exit\n");
    shell_destroy(&sh);
    return sh.should_exit ? sh.should_exit_status : sh.last_status;
}
