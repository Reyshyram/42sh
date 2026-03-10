/*
** EPITECH PROJECT, 2026
** execute_pipe.c
** File description:
** Execute pipe
*/

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/io.h"
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
        my_dprintf(STDERR_FILENO, "fork: %s.\n", strerror(errno));
        close_fds(fds);
        return false;
    }
    if (*left_pid == 0) {
        signal(SIGINT, SIG_DFL);
        dup2(fds[1], STDOUT_FILENO);
        close_fds(fds);
        exit(execute_ast(shell, ast->data.binary.left));
    }
    return true;
}

static bool execute_pipe_right(shell_t *shell, ast_node_t *ast, int fds[2],
    pid_t *right_pid)
{
    *right_pid = fork();
    if (*right_pid == -1) {
        my_dprintf(STDERR_FILENO, "fork: %s.\n", strerror(errno));
        close_fds(fds);
        return false;
    }
    if (*right_pid == 0) {
        signal(SIGINT, SIG_DFL);
        dup2(fds[0], STDIN_FILENO);
        close_fds(fds);
        exit(execute_ast(shell, ast->data.binary.right));
    }
    return true;
}

int execute_pipe(shell_t *shell, ast_node_t *ast)
{
    int fds[2];
    pid_t left_pid = 0;
    pid_t right_pid = 0;

    if (pipe(fds) == -1) {
        my_dprintf(STDERR_FILENO, "pipe: %s.\n", strerror(errno));
        return ERROR;
    }
    if (!execute_pipe_left(shell, ast, fds, &left_pid)) {
        close_fds(fds);
        return ERROR;
    }
    if (!execute_pipe_right(shell, ast, fds, &right_pid)) {
        close_fds(fds);
        return ERROR;
    }
    close_fds(fds);
    wait_for_subprocess(left_pid);
    return wait_for_subprocess(right_pid);
}
