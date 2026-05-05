/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/


#include "builtins.h"
#include "shell.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my/misc.h"

Test(working_if, easy)
{
    shell_t shell;
    bool our_env;
    char *argv[6] = {"if", "true", "==", "true", "ls", NULL};
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_if(&shell, 6, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(no_args_if, easy)
{
    shell_t shell;
    bool our_env;
    char *argv[1] = {"if",NULL};
    char **env = __environ;

    init_shell(&shell, env);
    our_env = builtin_if(&shell, 1, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(empty_if, easy)
{
    shell_t shell;
    bool our_env;
    char *argv[4] = {"if", "true", "==", "true",NULL};
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_if(&shell, 4, argv);
    cr_assert_eq(our_env, ERROR);
}
