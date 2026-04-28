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
#include "env.h"
#include <time.h>
#include <unistd.h>
#include "my/misc.h"

Test(working_exit, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_exit(&shell, 1, NULL);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(not_working_exit, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_exit(&shell, 3, NULL);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(working_exit, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"exit", "84"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_exit(&shell, 2, av);
    not_our_env = 84;
    cr_assert_eq(our_env, not_our_env);
}

Test(not_working_exit, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"exit", "oibsib"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_exit(&shell, 2, av);
    not_our_env = 84;
    cr_assert_eq(our_env, not_our_env);
}

Test(not_working_exit_2, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"exit", "8oibsib"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_exit(&shell, 2, av);
    not_our_env = 84;
    cr_assert_eq(our_env, not_our_env);
}
