/*
** EPITECH PROJECT, 2026
** execute_cmd.c
** File description:
** Execute a command
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/misc.h"
#include "my/strings.h"

#include "ast.h"
#include "builtins.h"
#include "env.h"
#include "executer.h"
#include "shell.h"

static void run_subprocess(char **argv, char *binary_path, char **env)
{
    signal(SIGINT, SIG_DFL);
    if (execve(binary_path ? binary_path : argv[0], argv, env) == -1) {
        if (errno == ENOEXEC)
            fprintf(stderr,
                "%s: Exec format error. Binary file not executable.\n",
                argv[0]);
        else
            fprintf(stderr, "%s: %s.\n", argv[0], strerror(errno));
        exit(ERROR);
    }
}

static int execute_fork(char **argv, char *binary_path, char ***env)
{
    pid_t pid = fork();

    if (pid == -1) {
        fprintf(stderr, "fork: %s.\n", strerror(errno));
        my_free_word_array(*env);
        return ERROR;
    }
    if (pid == 0)
        run_subprocess(argv, binary_path, *env);
    my_free_word_array(*env);
    return wait_for_subprocess(pid);
}

int execute_binary(shell_t *shell, char **argv, char *binary_path)
{
    char **env = env_to_word_array(shell->env);

    if (shell->env && !env) {
        fprintf(stderr, "env: Couldn't allocate memory for env conversion.\n");
        return ERROR;
    }
    return execute_fork(argv, binary_path, &env);
}

static int execute_local_binary(shell_t *shell, char **argv)
{
    struct stat st;

    if (access(argv[0], F_OK) == -1) {
        fprintf(stderr, "%s: Command not found.\n", argv[0]);
        return ERROR;
    }
    if ((stat(argv[0], &st) == 0 && S_ISDIR(st.st_mode))
        || access(argv[0], X_OK) == -1) {
        fprintf(stderr, "%s: Permission denied.\n", argv[0]);
        return ERROR;
    }
    return execute_binary(shell, argv, nullptr);
}

void print_permission_denied(char *cmd, char *current_dir)
{
    if (my_is_char_in_str(cmd, '/'))
        fprintf(stderr, "%s: Permission denied.\n", cmd);
    else
        fprintf(stderr, "%s/%s: Permission denied.\n", current_dir, cmd);
}

static int try_command(shell_t *shell, char **argv, char *current_dir,
    bool *cmd_executed)
{
    size_t binary_path_length = strlen(argv[0]) + strlen(current_dir) + 2;
    char binary_path[binary_path_length];
    struct stat st;

    sprintf(binary_path, "%s/%s", current_dir, argv[0]);
    if (access(binary_path, F_OK) == -1)
        return ERROR;
    if (stat(binary_path, &st) == 0 && S_ISDIR(st.st_mode))
        return ERROR;
    if (access(binary_path, X_OK) == -1) {
        print_permission_denied(argv[0], current_dir);
        *cmd_executed = true;
        return ERROR;
    }
    *cmd_executed = true;
    return execute_binary(shell, argv, binary_path);
}

static int execute_path_binary(shell_t *shell, char **argv)
{
    char *path_env = get_variable_value(shell->env, "PATH");
    size_t path_length = path_env ? strlen(path_env) : strlen(DEFAULT_PATH);
    char path_copy[path_length + 1];
    int status = 0;
    bool cmd_executed = false;

    if (!path_env)
        path_env = DEFAULT_PATH;
    strcpy(path_copy, path_env);
    for (char *current_dir = strtok(path_copy, ":"); current_dir;
        current_dir = strtok(nullptr, ":")) {
        status = try_command(shell, argv, current_dir, &cmd_executed);
        if (cmd_executed)
            return status;
    }
    fprintf(stderr, "%s: Command not found.\n", argv[0]);
    return ERROR;
}

int execute_cmd(shell_t *shell, ast_node_t *ast)
{
    for (size_t i = 0; BUILTINS[i].name; i++)
        if (!strcmp(ast->data.cmd.argv[0], BUILTINS[i].name))
            return BUILTINS[i].func(shell, ast->data.cmd.argc,
                ast->data.cmd.argv);
    if (my_is_char_in_str(ast->data.cmd.argv[0], '/'))
        return execute_local_binary(shell, ast->data.cmd.argv);
    return execute_path_binary(shell, ast->data.cmd.argv);
}
