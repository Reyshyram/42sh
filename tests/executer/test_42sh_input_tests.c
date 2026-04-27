/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/

#include "my/misc.h"
#include "shell.h"
#include <ncurses.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>


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

Test(input_wrong_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("hello"));
    cr_assert_eq(status, ERROR);
}

Test(input_ls_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("ls"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_multiple_ls_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("ls;ls;ls;ls;ls;ls"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_ls_redirect_into_no_perms_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("ls > tests/no_perms"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_simple_repeat_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("repeat 5 ls"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_simple_repeat_failed_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("repeat 5 qsdqsd"));
    cr_assert_eq(ERROR, status);
}

Test(input_simple_repeat_no_perm_command, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    mkdir("/tmp/no_perms", 0);
    status = handle_input(&shell, strdup("repeat 5 cat > /tmp/no_perms"));
    cr_assert_eq(ERROR, status);
}

Test(input_asterix_ls, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("ls  /bin/*t*"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_second_letter_ls, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;

    cr_redirect_stdout();
    init_shell(&shell, env);
    status = handle_input(&shell, strdup("ls  /bin/?t"));
    cr_assert_eq(SUCCESS, status);
}

Test(input_main_read_input, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;
    char *ln = NULL;

    cr_redirect_stdout();
    init_shell(&shell, env);
    fprintf(stdin, "hi hello || ls /bin");
    ln = read_input(shell.variables, shell.interactive, shell.last_status);
    cr_assert_eq(SUCCESS, status);
}

Test(input_right_arrow_input, easy)
{
    char **env = __environ;
    shell_t shell;
    int status = 0;
    char *ln = NULL;

    cr_redirect_stdout();
    init_shell(&shell, env);
    fprintf(stdin, "^A");
    ln = read_input(shell.variables, shell.interactive, shell.last_status);
    cr_assert_eq(SUCCESS, status);
}