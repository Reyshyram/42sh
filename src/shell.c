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

/*************************************
* The handle_sigint function handles the sigint for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int signal, an integer
*************************************/
void handle_sigint(int signal)
{
    (void) signal;
    write(STDOUT_FILENO, "\n", 1);
}

/*************************************
* The init_variables function initialises the vars for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @return -> a boolean, either true or false
*************************************/
bool init_variables(shell_t *shell)
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

/*************************************
* The init_shell function initialises the shell for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> char **env, an array of the env
*   @return -> a boolean, either true or false
*************************************/
bool init_shell(shell_t *shell, char **env)
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

/*************************************
* The shell_destroy function destroys the shell for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*************************************/
static void shell_destroy(shell_t *shell)
{
    my_free_list(shell->env, (void *) free_variable);
    my_free_list(shell->variables, (void *) free_variable);
    my_free_list(shell->aliases, (void *) free_variable);
}

/*************************************
* The show_error_message function shows the error message for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *parser, a struct found in include/parser.h
*************************************/
static void show_error_message(parser_t *parser)
{
    if (parser->error_message_prefix) {
        fprintf(stderr, "%s: %s\n", parser->error_message_prefix,
            parser->error_message);
        free(parser->error_message_prefix);
    } else
        fprintf(stderr, "%s\n", parser->error_message);
}

/*************************************
* The parse_ast function parses the ast for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t **ast, a struct found in include/ast.h
*   @param -> parser_t *parser, a struct found in include/parser.g
*   @return -> a boolean, either true or false
*************************************/
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

/*************************************
* The handle_parsing function handles the parsing for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t **ast, a struct found in include/ast.h
*   @param -> parser_t *parser, a struct found in include/parser.h
*   @return -> a boolean, either true or false
*************************************/
static bool handle_parsing(ast_node_t **ast, parser_t *parser)
{
    if (!parse_ast(ast, parser)) {
        if (!isatty(STDIN_FILENO))
            empty_stdin();
        return false;
    }
    return true;
}

/*************************************
* The destroy_parser_and_lexer function destroys the
* parser and the lexer for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> parser_t *parser, a struct found in include/parser.h
*   @param -> lexer_t *lexer, a struct found in include/lexer.h
*   @return -> an integer, either a success or an error
*************************************/
static int destroy_parser_and_lexer(parser_t *parser, lexer_t *lexer)
{
    parser_destroy(parser);
    lexer_destroy(lexer);
    return ERROR;
}

/*************************************
* The handle_input function handles the input for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> char *line, a string of the line
*   @return -> an integer, either a success or an error
*************************************/
int handle_input(shell_t *shell, char *line)
{
    parser_t parser;
    lexer_t lexer;
    ast_node_t *ast = nullptr;
    int status = 0;

    if (!line)
        return SUCCESS;
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

/*************************************
* The shell_run function runs the shell for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char **env, an array of the env
*   @return -> an integer, either a success or an error
*************************************/
int shell_run(char **env)
{
    shell_t sh;
    char *line = nullptr;

    if (!init_shell(&sh, env)) {
        fprintf(stderr, "memory: couldn't allocate memory for the shell\n");
        return ERROR;
    }
    while (true) {
        line = read_input(&sh, sh.interactive, sh.last_status);
        if (!line && should_exit_if_eof(&sh))
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
