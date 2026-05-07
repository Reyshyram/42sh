/*
** EPITECH PROJECT, 2026
** cd.c
** File description:
** cd builtin
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "my/misc.h"

#include "shell.h"

static bool update_variables(shell_t *shell)
{
    char *curr_dir = getcwd(nullptr, 0);
    char *previous_dir = get_variable_value(shell->variables, "cwd");

    if (!curr_dir)
        return false;
    if (!set_variable(&shell->variables, "owd", previous_dir)
        || !set_variable(&shell->variables, "cwd", curr_dir)
        || !set_variable(&shell->env, "PWD", curr_dir)) {
        free(curr_dir);
        return false;
    }
    free(curr_dir);
    return true;
}

static int cd_to_home(shell_t *shell)
{
    char *home = get_variable_value(shell->variables, "home");

    if (!home) {
        fprintf(stderr, "cd: No home directory.\n");
        return ERROR;
    }
    if (chdir(home) == -1) {
        fprintf(stderr, "cd: Can't change to home directory.\n");
        return ERROR;
    }
    if (!update_variables(shell)) {
        fprintf(stderr, "cd: Couldn't update shell variables.\n");
        return ERROR;
    }
    return SUCCESS;
}

static int cd_to_prev_directory(shell_t *shell)
{
    char *previous_dir = get_variable_value(shell->variables, "owd");

    if (!previous_dir) {
        fprintf(stderr, ": No such file or directory.\n");
        return ERROR;
    }
    if (chdir(previous_dir) == -1) {
        fprintf(stderr, "%s: %s.\n", previous_dir, strerror(errno));
        return ERROR;
    }
    if (!update_variables(shell)) {
        fprintf(stderr, "cd: Couldn't update shell variables.\n");
        return ERROR;
    }
    return SUCCESS;
}

static int cd_to_directory(shell_t *shell, char *dir)
{
    if (dir[0] == '-' && !dir[1])
        return cd_to_prev_directory(shell);
    if (chdir(dir) == -1) {
        fprintf(stderr, "%s: %s.\n", dir, strerror(errno));
        return ERROR;
    }
    if (!update_variables(shell)) {
        fprintf(stderr, "cd: Couldn't update shell variables.\n");
        return ERROR;
    }
    return SUCCESS;
}

static void execute_cwdcmd(shell_t *shell)
{
    char *cwdcmd = get_variable_value(shell->aliases, "cwdcmd");
    char *copy = nullptr;

    if (!cwdcmd)
        return;
    copy = strdup(cwdcmd);
    if (!copy)
        return;
    handle_input(shell, copy);
    free(copy);
}

int builtin_cd(shell_t *shell, size_t argc, char **argv)
{
    int status = 0;

    if (argc == 1) {
        status = cd_to_home(shell);
        if (status == SUCCESS)
            execute_cwdcmd(shell);
        return status;
    }
    if (argc > 2) {
        fprintf(stderr, "cd: Too many arguments.\n");
        return ERROR;
    }
    status = cd_to_directory(shell, argv[1]);
    if (status == SUCCESS)
        execute_cwdcmd(shell);
    return status;
}
