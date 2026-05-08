/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** builtin_which
*/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "my/misc.h"

#include "builtins.h"
#include "env.h"
#include "shell.h"

/*************************************
* The try_command_which function tries the which command for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *cmd, a string of the command
*   @param -> char *current_dir, a string of the directory
*   @return -> a boolean, either true or false
*************************************/
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
    if (access(binary_path, X_OK) == -1)
        return false;
    printf("%s\n", binary_path);
    return true;
}

/*************************************
* The whhich_for_loop function handles the which's loop for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *path_env, a string of the path
*   @param -> char *cmd, a string of the command
*   @return -> a boolean, either true or false
*************************************/
static bool which_for_loop(char *path_env, char *cmd)
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

/*************************************
* The call_tests_which function calls the tests for the which for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *aliased_cmd, a string of the cmd
*   @param -> char **argv, an array of the args
*   @param -> size_t i, the size of i
*   @param -> char *path_env, a string of the path
*   @return -> a boolean, either true or false
*************************************/
static bool call_tests_which(char *aliased_cmd, char **argv, size_t i,
    char *path_env)
{
    if (aliased_cmd) {
        printf("%s: \t aliased to %s\n", argv[i], aliased_cmd);
        return true;
    }
    for (size_t j = 0; BUILTINS[j].name; j++)
        if (!strcmp(argv[i], BUILTINS[j].name)) {
            printf("%s: shell built-in command.\n", argv[i]);
            return true;
        }
    if (!which_for_loop(path_env, argv[i])) {
        fprintf(stderr, "%s: Command not found.\n", argv[i]);
        return false;
    }
    return true;
}

/*************************************
* The builtin_which function handles the builtin where for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> char *aliased_cmd, a string of the cmd
*   @param -> size_t argc, the size of the arg
*   @param -> char **argv, an array of the args
*   @return -> an integer, either an error or a success
*************************************/
int builtin_which(shell_t *shell, size_t argc, char **argv)
{
    bool success = true;
    char *path_env = get_variable_value(shell->env, "PATH");
    char *aliased_cmd = NULL;

    if (!path_env)
        path_env = DEFAULT_PATH;
    if (argc < 2) {
        fprintf(stderr, "which: Too few arguments.\n");
        return ERROR;
    }
    for (size_t i = 1; i < argc; i++) {
        aliased_cmd = get_variable_value(shell->aliases, argv[i]);
        if (!call_tests_which(aliased_cmd, argv, i, path_env))
            success = false;
    }
    return success ? SUCCESS : ERROR;
}
