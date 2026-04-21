/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/


#include "builtins.h"
#include "my/list.h"
#include "my/strings.h"
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
#include "my/list.h"
#include "my/misc.h"

#include "ast.h"
#include "env.h"
#include "executer.h"
#include "lexer.h"
#include "parser.h"
#include "shell.h"


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
