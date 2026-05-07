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

Test(working_alias_unalias, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[3] = {"alias", "ls", "thing", NULL};
    char *argv2[2] = {"unalias", "thing", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_alias(&shell, argc, argv);
    builtin_unalias(&shell, argc, argv2);
    cr_assert_eq(our_env, SUCCESS);
}

Test(print_one_alias, easy)
{
    shell_t shell;
    int argc = 2;
    char *argv[2] = {"alias", "ls", NULL};
    char *argv2[2] = {"unalias", "thing", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_alias(&shell, argc, argv);
    builtin_unalias(&shell, argc, argv2);
    cr_assert_eq(our_env, SUCCESS);
}

Test(working_alias_unalias_multiple, easy)
{
    shell_t shell;
    int argc = 5;
    char *argv[5] = {"alias", "ls", "thing", "cat", "woah", NULL};
    char *argv2[3] = {"unalias", "thing", "woah", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_alias(&shell, argc, argv);
    builtin_unalias(&shell, 3, argv2);
    cr_assert_eq(our_env, SUCCESS);
}

Test(single_alias, easy)
{
    shell_t shell;
    int argc = 1;
    char *argv[1] = {"alias", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_alias(&shell, argc, argv);
    cr_assert_eq(our_env, SUCCESS);
}

Test(single_unalias, easy)
{
    shell_t shell;
    int argc = 1;
    char *argv[1] = {"unalias", NULL};
    bool our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_unalias(&shell, argc, argv);
    cr_assert_eq(our_env, ERROR);
}
