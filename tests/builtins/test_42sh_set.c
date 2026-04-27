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
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include "my/misc.h"


static void handle_sigint([[maybe_unused]] int signal)
{
    write(STDOUT_FILENO, "\n", 1);
}

static bool init_variables(shell_t *shell)
{
    char *home = get_variable_value(shell->env, "HOME");
    char *cwd = getcwd(nullptr, 0);

    if (!cwd)
        return false;
    if (home && !set_variable(&shell->variables, "home", home))
        return false;
    if (!set_variable(&shell->variables, "cwd", cwd))
        return false;
    free(cwd);
    return true;
}

static bool init_shell(shell_t *shell, char **env)
{
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->should_exit = false;
    shell->is_subprocess = false;
    shell->is_out_redirected = false;
    shell->is_in_redirected = false;
    shell->env = env_to_list(env);
    shell->variables = nullptr;
    if (!shell->env && *env)
        return false;
    if (shell->interactive && signal(SIGINT, handle_sigint) == SIG_ERR)
        return false;
    return init_variables(shell);
}

Test(working_set_new, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[3] = {"set", "qsds_dqds", NULL};

    init_shell(&shell, env);
    cr_redirect_stdout();
    our_env = builtin_set(&shell, 3, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(already_set_var, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"set", strdup("home")};

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 2, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(no_arg_set, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 1, nullptr);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(bad_variable_name_set, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"set", "-74747", NULL};

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 2, av);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(bad_variable_name_set2, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"set", "74_747"};

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 2, av);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(bad_variable_name_set3, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[2] = {"set", "=74747"};

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 2, av);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}

Test(multiple_vars_set, medium)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;
    char *av[6] = {"set", strdup("sqdsqd"), strdup("qd=sd"), strdup("dq=sd=qd"), strdup("sqdsqdsd"), NULL};

    init_shell(&shell, env);
    our_env = builtin_set(&shell, 5, av);
    not_our_env = SUCCESS;
    cr_assert_eq(our_env, not_our_env);
}

Test(no_arg_unset, easy)
{
    shell_t shell;
    bool our_env;
    bool not_our_env;
    char **env = __environ;

    init_shell(&shell, env);
    our_env = builtin_unset(&shell, 1, nullptr);
    not_our_env = ERROR;
    cr_assert_eq(our_env, not_our_env);
}
