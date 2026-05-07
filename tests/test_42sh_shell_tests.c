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
#include <sys/stat.h>
#include <unistd.h>

Test(shell_run_long_command, medium)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "ls > /tmp/ha.txt; ls < cat /tmp/ha.txt || ls .. > /tmp/ha.txt; ls /bin/ca*");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_simple_exit, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "exit\n");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_simple_builtins, easy)
{
    char **env = __environ;
    int status = -1;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "unsetenv thing; unsetenv PATH; unsetenv home; cd ..\n");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_backslash_endline, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "ls \\\
        /bin/ls\n");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, 2);
}

Test(shell_heredoc, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "ls << END\n");
    fprintf(f, "..\n");
    fprintf(f, "../..\n");
    fprintf(f, "/bin/\n");
    fprintf(f, "END\n");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_random_sentence, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "oh woah look at this test");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, ERROR);
}

Test(shell_random_command, easy)
{
    char **env = __environ;
    int status = 0;

    cr_redirect_stdout();
    FILE *f = cr_get_redirected_stdin();
    fprintf(f, "ls > /tmp/ha; echo \"hi\" || thingy && repeat 1 ls; repeat -1 ls");
    fclose(f);
    status = shell_run(env);
    cr_assert_eq(status, SUCCESS);
}

Test(shell_empty_stdin, easy)
{
    cr_redirect_stdout();
    cr_redirect_stdin();
    fprintf(stdin, "which ls");
    empty_stdin();
    cr_assert_eq(feof(stdin), SUCCESS);
}
