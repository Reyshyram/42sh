/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** builtin_where
*/

#include "env.h"
#include "executer.h"
#include "my/misc.h"
#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int try_command_where(char **argv, char *current_dir)
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
        return ERROR;
    }
    printf("%s", binary_path);
    return SUCCESS;
}

int builtin_where(shell_t *shell, [[maybe_unused]] size_t argc, char **argv)
{
    int status = 0;
    char *path_env = get_variable_value(shell->env, "PATH");
    size_t path_length = path_env ? strlen(path_env) : strlen(DEFAULT_PATH);
    char path_copy[path_length + 1];

    for (char *current_dir = strtok(path_copy, ":"); current_dir;
        current_dir = strtok(nullptr, ":")) {
        status = try_command_where(argv, current_dir);
        return status;
    }
    return ERROR;
}
