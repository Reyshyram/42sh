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

/*************************************
* The read_pipe_output function reads the pipe's
* output for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> pipe_fd, an integer
*   @return -> a string, either nullptr or the buffer
*************************************/
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

/*************************************
* The remove_end_newlines function removes the
* newlines at the end for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> output, a string
*************************************/
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

/*************************************
* The run_command_substitutions function runs the command
* substitutions for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> command, a string
*   @param -> output_fd, an integer
*************************************/
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

/*************************************
* The handle_pipe_error function handles all the
* pipe errors for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @return -> a string, either nullptr or the error message
*************************************/
static char *handle_pipe_error(void)
{
    fprintf(stderr, "pipe: %s.\n", strerror(errno));
    return nullptr;
}

/*************************************
* The handle_fork_error function handles all the
* fork errors for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> fds[2], an integer
*   @return -> a string, either nullptr or the error message
*************************************/
static char *handle_fork_error(int fds[2])
{
    fprintf(stderr, "fork: %s.\n", strerror(errno));
    close(fds[0]);
    close(fds[1]);
    return nullptr;
}

/*************************************
* The execute_command_substitution function executes
* the command substitutioins for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> shell_t *shell, a struct found in include/shell.h
*   @param -> command, a string
*   @return -> a string, either another function or the output
*************************************/
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
