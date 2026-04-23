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
