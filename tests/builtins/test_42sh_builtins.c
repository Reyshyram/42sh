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
#include <unistd.h>
#include "my/misc.h"

Test(working_builtins, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_builtins(&shell, 1, NULL);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(not_working_builtins, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    our_env = builtin_builtins(&shell, 2, NULL);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}
