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

int builtin_env(shell_t *shell, size_t argc, char **argv);

static const builtin_t BUILTINS[] = {
    {"env", builtin_env},
    {nullptr, nullptr},
};

#endif /* BUILTINS_H */
