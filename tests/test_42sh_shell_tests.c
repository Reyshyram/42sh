/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/

#include "my/misc.h"
#include "shell.h"
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

Test(shell_run_long_command, medium)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "ls > /tmp/ha.txt; ls < cat /tmp/ha.txt || ls .. > /tmp/ha.txt; ls /bin/ca* && ls /bin/[0-9][0-9] || ls /bin.{/cat, /ls}");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_simple_exit, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "exit\n");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_simple_builtins, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "unsetenv thing; unsetenv PATH; unsetenv home; cd ..\n");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_backslash_endline, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "ls \\\
        /bin/ls\n");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_heredoc, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "ls << END\
        ls");
    fprintf(stdin, "..");
    fprintf(stdin, "../..");
    fprintf(stdin, "/bin/");
    fprintf(stdin, "END");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_random_sentence, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "oh woah look at this test");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_random_command, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    fprintf(stdin, "ls > /tmp/ha; [echo \"hi\" || thingy] && repeat 1 ls; repeat -1 ls");
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}
