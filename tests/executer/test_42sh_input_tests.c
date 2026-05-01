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
#include <sys/stat.h>
#include <unistd.h>

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

