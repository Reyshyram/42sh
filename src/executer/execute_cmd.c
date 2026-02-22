/*
** EPITECH PROJECT, 2026
** execute_cmd.c
** File description:
** Execute a command
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "my/io.h"
#include "my/misc.h"
#include "my/strings.h"

#include "ast.h"
#include "builtins.h"
#include "env.h"
#include "executer.h"
#include "shell.h"

int execute_binary(shell_t *shell, char **argv)
{
    pid_t pid = 0;
    char **env = env_to_word_array(shell->env);

    if (shell->env && !env) {
        my_puterr("env: Couldn't allocate memory for env conversion.\n");
        return ERROR;
    }
    pid = fork();
    if (pid == -1) {
        my_dprintf(STDERR_FILENO, "fork: %s.\n", strerror(errno));
        my_free_word_array(env);
        return ERROR;
    }
    if (pid == 0)
        if (execve(argv[0], argv, env) == -1) {
            my_dprintf(STDERR_FILENO, "execve: %s.\n", strerror(errno));
            exit(ERROR);
        }
    my_free_word_array(env);
    return wait_for_subprocess(pid);
}

int execute_local_binary(shell_t *shell, char **argv)
{
    struct stat st;

    if (access(argv[0], F_OK) == -1) {
        my_dprintf(STDERR_FILENO, "%s: Command not found.\n", argv[0]);
        return ERROR;
    }
    if ((stat(argv[0], &st) == 0 && S_ISDIR(st.st_mode))
        || access(argv[0], X_OK) == -1) {
        my_dprintf(STDERR_FILENO, "%s: Permission denied.\n", argv[0]);
        return ERROR;
    }
    return execute_binary(shell, argv);
}

int execute_cmd(shell_t *shell, ast_node_t *ast)
{
    for (size_t i = 0; BUILTINS[i].name; i++)
        if (!my_strcmp(ast->data.cmd.argv[0], BUILTINS[i].name))
            return BUILTINS[i].func(shell, ast->data.cmd.argc,
                ast->data.cmd.argv);
    if (my_is_char_in_str(ast->data.cmd.argv[0], '/'))
        return execute_local_binary(shell, ast->data.cmd.argv);
    return SUCCESS;
}
