/*
** EPITECH PROJECT, 2026
** shell.c
** File description:
** shell.c
*/

#include <stdlib.h>
#include <unistd.h>

#include "my/io.h"
#include "my/misc.h"

#include "ast.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"

static bool init_shell(shell_t *shell, char **env)
{
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->env = my_copy_word_array(env);
    if (!shell->env)
        return false;
    return true;
}

static void shell_destroy(shell_t *shell)
{
    my_free_word_array(shell->env);
}

static bool parse_ast(ast_node_t **ast, parser_t *parser)
{
    *ast = parser_parse(parser);
    if (!*ast) {
        if (!parser->error_message)
            return true;
        my_dprintf(STDERR_FILENO, "%s\n", parser->error_message);
        return false;
    }
    return true;
}

int handle_input(shell_t *shell, char *line)
{
    parser_t parser;
    lexer_t lexer;
    ast_node_t *ast = nullptr;

    lexer_init(&lexer, line, shell);
    parser_init(&parser, &lexer);
    if (parser.error_message) {
        my_dprintf(STDERR_FILENO, "%s\n", parser.error_message);
        parser_destroy(&parser);
        return ERROR;
    }
    if (!parse_ast(&ast, &parser)) {
        parser_destroy(&parser);
        return ERROR;
    }
    parser_destroy(&parser);
    ast_destroy(ast);
    return SUCCESS;
}

int shell_run(char **env)
{
    shell_t shell;
    char *line = nullptr;

    if (!init_shell(&shell, env)) {
        my_puterr("memory: couldn't allocate memory for the shell\n");
        return ERROR;
    }
    while (true) {
        line = read_input(shell.env, shell.interactive, shell.last_status);
        if (!line)
            break;
        shell.last_status = handle_input(&shell, line);
        free(line);
    }
    if (shell.interactive)
        my_putstr("exit\n");
    shell_destroy(&shell);
    return shell.last_status;
}
