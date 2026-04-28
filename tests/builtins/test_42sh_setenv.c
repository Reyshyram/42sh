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

Test(working_setenv_new, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[3] = {"setenv", "qsdsdqds", "NEWTHING"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_setenv(&shell, 3, av);
    not_our_env = 0;
    cr_assert_eq(our_env, not_our_env);
}

Test(working_setenv_update, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[3] = {"setenv", "HOME", "NEWTHING"};

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 3, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(setenv_null, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"setenv", "NULL"};

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 2, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(no_arg_setenv, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 1, NULL);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(too_many_args_setenv, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 7, NULL);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(bad_variable_name_setenv, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"setenv", "-74747"};

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 2, av);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(alphanumeric_in_setenv, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"setenv", "qsdsqd=="};

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_setenv(&shell, 2, av);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(no_arg_unsetenv, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    cr_redirect_stdout();
    init_shell(&shell, env);
    our_env = builtin_unsetenv(&shell, 1, nullptr);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}
