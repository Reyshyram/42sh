/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** builtin_which
*/

#include "env.h"
#include "executer.h"
#include "my/misc.h"
#include "shell.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static bool try_command_which(char *cmd, char *current_dir)
{
    size_t binary_path_length = strlen(cmd) + strlen(current_dir) + 2;
    char binary_path[binary_path_length];
    struct stat st;

    sprintf(binary_path, "%s/%s", current_dir, cmd);
    if (access(binary_path, F_OK) == -1)
        return false;
    if (stat(binary_path, &st) == 0 && S_ISDIR(st.st_mode))
        return false;
    if (access(binary_path, X_OK) == -1) {
        print_permission_denied(cmd, current_dir);
        return false;
    }
    printf("%s\n", binary_path);
    return true;
}

bool which_for_loop(char *path_env, char *cmd)
{
    size_t path_length = strlen(path_env);
    char path_copy[path_length + 1];

    strcpy(path_copy, path_env);
    for (char *current_dir = strtok(path_copy, ":"); current_dir;
        current_dir = strtok(nullptr, ":")) {
        if (try_command_which(cmd, current_dir))
            return true;
    }
    return false;
}

int builtin_which(shell_t *shell, size_t argc, char **argv)
{
    bool success = true;
    char *path_env = get_variable_value(shell->env, "PATH");

    if (!path_env)
        path_env = DEFAULT_PATH;
    if (argc < 2) {
        fprintf(stderr, "which: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++)
        if (!which_for_loop(path_env, argv[i]))
            success = false;
    return success ? SUCCESS : ERROR;
}
