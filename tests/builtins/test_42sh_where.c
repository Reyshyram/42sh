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

Test(working_where_ls, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"where", "ls", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(not_working_where, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"where", "lqsddqssqddsqdqsdqssqddqss", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(low_argc_where, easy)
{
    shell_t shell;
    int argc = 1;
    char *argv[2] = {"where", "lqsddqssqddsqdqsdqssqddqss", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(multiple_where, easy)
{
    shell_t shell;
    int argc = 3;
    char *argv[3] = {"where", "ls", "cat", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(where_directory, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"where", "/lib", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(where_no_perms, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"where", "/tests/no_perms", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_where(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}
