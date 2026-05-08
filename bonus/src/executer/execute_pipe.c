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

static void close_fds(int fds[2])
{
    close(fds[0]);
    close(fds[1]);
}

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
        shell->is_subprocess = true;
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
