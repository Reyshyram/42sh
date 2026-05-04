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

Test(working_which_ls, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"which", "ls", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(not_working_which, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"which", "lqsddqssqddsqdqsdqssqddqss", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(low_argc_which, easy)
{
    shell_t shell;
    int argc = 1;
    char *argv[2] = {"which", "lqsddqssqddsqdqsdqssqddqss", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(multiple_which, easy)
{
    shell_t shell;
    int argc = 3;
    char *argv[3] = {"which", "ls", "cat", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(which_directory, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"which", "/lib", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}

Test(which_no_perms, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"which", "/tests/no_perms", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_which(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}
