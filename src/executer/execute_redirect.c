/*
** EPITECH PROJECT, 2026
** execute_redirect.c
** File description:
** Execute redirect
*/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/misc.h"

#include "ast.h"
#include "executer.h"
#include "shell.h"

/*************************************
* The is_heredoc_delim function verifies if there
* is a delimitation for the heredoc for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *line, a string of the line
*   @param -> ssize_t line_length, the size of the line
*   @param -> char *heredoc_delim, the string of the delimitation
*   @return -> a boolean, either true or false
*************************************/
static bool is_heredoc_delim(char *line, ssize_t line_length,
    char *heredoc_delim)
{
    size_t delim_length = strlen(heredoc_delim);

    if (line_length < 0)
        return false;
    if (strncmp(line, heredoc_delim, delim_length) != 0)
        return false;
    return line[delim_length] == '\0' || line[delim_length] == '\n';
}

/*************************************
* The get_heredoc_input function gets the heredoc input for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @param -> int fd, an integer
*   @return -> a boolean, either true or false
*************************************/
static bool get_heredoc_input(ast_node_t *ast, int fd)
{
    char *line = nullptr;
    size_t size = 0;
    ssize_t line_length = 0;

    while (true) {
        if (isatty(STDIN_FILENO))
            printf("? ");
        line_length = getline(&line, &size, stdin);
        if (line_length == -1)
            break;
        if (is_heredoc_delim(line, line_length, ast->data.redirect.file))
            break;
        if (write(fd, line, line_length) != line_length) {
            free(line);
            return false;
        }
    }
    free(line);
    return true;
}

/*************************************
* The heredoc_fd function handles the heredoc fd for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either an error or a success
*************************************/
static int heredoc_fd(ast_node_t *ast)
{
    int fds[2];

    if (pipe(fds) == -1) {
        fprintf(stderr, "pipe: %s.\n", strerror(errno));
        return -1;
    }
    if (!get_heredoc_input(ast, fds[1])) {
        fprintf(stderr, "write: %s.\n", strerror(errno));
        close(fds[0]);
        close(fds[1]);
        return -1;
    }
    close(fds[1]);
    return fds[0];
}

/*************************************
* The open_redirect_fd function opens the redirs fd for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either an error or a success
*************************************/
static int open_redirect_fd(ast_node_t *ast)
{
    int flags = 0;
    int perms = 0644;

    if (ast->data.redirect.fd == STDIN_FILENO && ast->data.redirect.append)
        return heredoc_fd(ast);
    if (ast->data.redirect.fd == STDOUT_FILENO) {
        flags = O_WRONLY | O_CREAT;
        flags |= ast->data.redirect.append ? O_APPEND : O_TRUNC;
        return open(ast->data.redirect.file, flags, perms);
    }
    return open(ast->data.redirect.file, O_RDONLY);
}

/*************************************
* The setup_redirection function sets the redirs up for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @param -> int *old_fd, an array of integer
*   @return -> a boolean, either true or false
*************************************/
static bool setup_redirection(ast_node_t *ast, int *old_fd)
{
    int fd = ast->data.redirect.fd;
    int current_fd = open_redirect_fd(ast);

    if (current_fd == -1) {
        if (!(ast->data.redirect.fd == STDIN_FILENO
                && ast->data.redirect.append))
            fprintf(stderr, "%s: %s.\n", ast->data.redirect.file,
                strerror(errno));
        return false;
    }
    *old_fd = dup(fd);
    if (dup2(current_fd, fd) == -1) {
        fprintf(stderr, "dup2: %s.\n", strerror(errno));
        close(current_fd);
        close(*old_fd);
        return false;
    }
    close(current_fd);
    return true;
}

/*************************************
* The restore_fd function restores the fd for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int old_fd, an integer
*   @param -> int fd, an integer
*   @return -> a boolean, either true or false
*************************************/
static bool restore_fd(int old_fd, int fd)
{
    if (dup2(old_fd, fd) == -1) {
        fprintf(stderr, "dup2: %s.\n", strerror(errno));
        close(old_fd);
        return false;
    }
    close(old_fd);
    return true;
}

/*************************************
* The redirection_execution function handles the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either an error or a success
*************************************/
static int redirect_execution(shell_t *shell, ast_node_t *ast)
{
    int status = 0;
    int old_fd = -1;
    int fd = ast->data.redirect.fd;

    if (!setup_redirection(ast, &old_fd))
        return ERROR;
    if (fd == STDOUT_FILENO)
        shell->is_out_redirected = true;
    if (fd == STDIN_FILENO)
        shell->is_in_redirected = true;
    status = execute_ast(shell, ast->data.redirect.node);
    if (!restore_fd(old_fd, fd))
        return ERROR;
    return status;
}

/*************************************
* The execute_redirect function executes the redirs for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either an error or a success
*************************************/
int execute_redirect(shell_t *shell, ast_node_t *ast)
{
    bool previous_is_out_redirected = shell->is_out_redirected;
    bool previous_is_in_redirected = shell->is_in_redirected;
    int status = 0;

    status = redirect_execution(shell, ast);
    shell->is_out_redirected = previous_is_out_redirected;
    shell->is_in_redirected = previous_is_in_redirected;
    return status;
}
