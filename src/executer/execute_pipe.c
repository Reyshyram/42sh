/*
** EPITECH PROJECT, 2026
** execute_pipe.c
** File description:
** Execute pipe
*/

#include <errno.h>
#include <signal.h>
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
* The close_fds function close the fds for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int fds[2], an integer
*************************************/
static void close_fds(int fds[2])
{
    close(fds[0]);
    close(fds[1]);
}

/*************************************
* The execute_pipe_left function executes the
* pipe when it's on the left for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @param -> int fds[2], an integer
*   @param -> pid_t *left_pid, a struct found in include/pid.h
*   @return -> a boolean, either true or false
*************************************/
static bool execute_pipe_left(shell_t *shell, ast_node_t *ast, int fds[2],
    pid_t *left_pid)
{
    *left_pid = fork();
    if (*left_pid == -1) {
        fprintf(stderr, "fork: %s.\n", strerror(errno));
        close_fds(fds);
        return false;
    }
    if (*left_pid == 0) {
        signal(SIGINT, SIG_DFL);
        shell->is_out_redirected = true;
        if (dup2(fds[1], STDOUT_FILENO) == -1) {
            fprintf(stderr, "dup2: %s.\n", strerror(errno));
            close_fds(fds);
            exit(ERROR);
        }
        close_fds(fds);
        exit(execute_ast(shell, ast->data.binary.left));
    }
    return true;
}

/*************************************
* The restore_stdin function restores the stdin for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int original_stdin, an integer
*   @return -> an integer, an error or a success
*************************************/
static bool restore_stdin(int original_stdin)
{
    if (dup2(original_stdin, STDIN_FILENO) == -1) {
        fprintf(stderr, "dup2: %s.\n", strerror(errno));
        close(original_stdin);
        return false;
    }
    close(original_stdin);
    return true;
}

/*************************************
* The execute_pipe_right function executes the
* pipe when it's on the right for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @param -> int fds[2], an integer
*   @param -> pid_t *left_pid, a struct found in include/pid.h
*   @return -> an integer, either a success or an error
*************************************/
static int execute_pipe_right(shell_t *shell, ast_node_t *ast, int fds[2])
{
    int original_stdin = dup(STDIN_FILENO);
    int status = 0;
    bool previous_is_in_redirected = shell->is_in_redirected;

    if (original_stdin == -1 || dup2(fds[0], STDIN_FILENO) == -1) {
        fprintf(stderr, "dup: %s.\n", strerror(errno));
        if (original_stdin != -1)
            close(original_stdin);
        close_fds(fds);
        return ERROR;
    }
    close_fds(fds);
    shell->is_in_redirected = true;
    status = execute_ast(shell, ast->data.binary.right);
    shell->is_in_redirected = previous_is_in_redirected;
    if (!restore_stdin(original_stdin))
        return ERROR;
    return status;
}

/*************************************
* The execute_pipe_left function executes the pipe for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, structure found in include/shell.h
*   @param -> ast_node_t *ast, a struct found in include/ast.h
*   @return -> an integer, either a success or an error
*************************************/
int execute_pipe(shell_t *shell, ast_node_t *ast)
{
    int fds[2];
    pid_t left_pid = 0;
    int right_status = 0;

    if (pipe(fds) == -1) {
        fprintf(stderr, "pipe: %s.\n", strerror(errno));
        return ERROR;
    }
    if (!execute_pipe_left(shell, ast, fds, &left_pid)) {
        close_fds(fds);
        return ERROR;
    }
    right_status = execute_pipe_right(shell, ast, fds);
    wait_for_subprocess(left_pid);
    return right_status;
}
