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

Test(working_cd, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"cd", ".."};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_cd(&shell, 2, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(not_working_cd, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_cd(&shell, 3, NULL);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(cd_home, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_cd(&shell, 1, NULL);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(no_home_cd, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"unsetenv", "HOME"};
    char *av2[2] = {"unsetenv", "home"};

    init_shell(&shell, env);
    builtin_unsetenv(&shell, 2, av);
    builtin_unset(&shell, 2, av2);
    cr_redirect_stdout();
    our_env = builtin_cd(&shell, 1, NULL);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(cd_to_non_existant, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av2[2] = {"cd", "libsqd"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_cd(&shell, 2, av2);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(cd_to_previous, hard)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"cd", ".."};
    char *av2[2] = {"cd", "-"};

    init_shell(&shell, env);
    cr_redirect_stdout();
    builtin_cd(&shell, 2, av);
    our_env = builtin_cd(&shell, 2, av2);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}
