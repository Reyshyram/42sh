/*
** EPITECH PROJECT, 2025
** builtins.h
** File description:
** Shell builtins
*/

#ifndef BUILTINS_H
// clang-format off
    #define BUILTINS_H

    #include "shell.h"
// clang-format on

typedef int (*builtin_func_t)(shell_t *shell, size_t argc, char **argv);

typedef struct {
    char *name;
    builtin_func_t func;
} builtin_t;

int builtin_builtins([[maybe_unused]] shell_t *shell, size_t argc,
    [[maybe_unused]] char **argv);

int builtin_env(shell_t *shell, size_t argc, char **argv);
int builtin_setenv(shell_t *shell, size_t argc, char **argv);
int builtin_unsetenv(shell_t *shell, size_t argc, char **argv);

int builtin_set(shell_t *shell, size_t argc, char **argv);
int builtin_unset(shell_t *shell, size_t argc, char **argv);

int builtin_cd(shell_t *shell, size_t argc, char **argv);

int builtin_exit(shell_t *shell, size_t argc, char **argv);

int builtin_which(shell_t *shell, [[maybe_unused]] size_t argc, char **argv);
int builtin_where(shell_t *shell, [[maybe_unused]] size_t argc, char **argv);

static const builtin_t BUILTINS[] = {
    {"builtins", builtin_builtins},
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"set", builtin_set},
    {"unset", builtin_unset},
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {"where", builtin_where},
    {"which", builtin_which},
    {nullptr, nullptr},
};

#endif /* BUILTINS_H */
