/*
** EPITECH PROJECT, 2026
** execute_command_substitution.c
** File description:
** Execute command substitution
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/misc.h"
#include "my/strings.h"

#include "executer.h"
#include "shell.h"

static char *read_pipe_output(int pipe_fd)
{
    char tmp_buffer[4096];
    ssize_t read_size = 0;
    char *buffer = nullptr;
    size_t buffer_size = 0;

    while (true) {
        read_size = read(pipe_fd, tmp_buffer, sizeof(tmp_buffer));
        if (read_size == 0)
            break;
        if (read_size < 0) {
            fprintf(stderr, "read: %s.\n", strerror(errno));
            free(buffer);
            return nullptr;
        }
        buffer = append_to_buffer(buffer, &buffer_size, tmp_buffer, read_size);
        if (!buffer)
            return nullptr;
    }
    return buffer ? buffer : strdup("");
}

static void remove_end_newlines(char *output)
{
    size_t len = 0;

    if (!output)
        return;
    len = strlen(output);
    while (len > 0 && output[len - 1] == '\n') {
        len--;
        output[len] = '\0';
    }
}

static void run_command_substitution(shell_t *shell, char *command,
    int output_fd)
{
    int status = 0;

    if (dup2(output_fd, STDOUT_FILENO) == -1) {
        fprintf(stderr, "dup2: %s.\n", strerror(errno));
        exit(ERROR);
    }
    close(output_fd);
    shell->is_out_redirected = false;
    shell->is_in_redirected = false;
    status = handle_input(shell, command);
    exit(status);
}

static char *handle_pipe_error(void)
{
    fprintf(stderr, "pipe: %s.\n", strerror(errno));
    return nullptr;
}

static char *handle_fork_error(int fds[2])
{
    fprintf(stderr, "fork: %s.\n", strerror(errno));
    close(fds[0]);
    close(fds[1]);
    return nullptr;
}

char *execute_command_substitution(shell_t *shell, char *command)
{
    int fds[2];
    pid_t pid = 0;
    char *output = nullptr;

    if (pipe(fds) == -1)
        return handle_pipe_error();
    pid = fork();
    if (pid == -1)
        return handle_fork_error(fds);
    if (pid == 0) {
        close(fds[0]);
        run_command_substitution(shell, command, fds[1]);
    }
    close(fds[1]);
    output = read_pipe_output(fds[0]);
    close(fds[0]);
    wait_for_subprocess(pid);
    remove_end_newlines(output);
    return output;
}
