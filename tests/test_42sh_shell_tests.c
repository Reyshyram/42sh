/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** simple_test
*/

#include "env.h"
#include "my/misc.h"
#include "shell.h"
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

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
