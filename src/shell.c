/*
** EPITECH PROJECT, 2026
** shell.c
** File description:
** shell.c
*/

#include "my/io.h"
#include "my/misc.h"

#include "shell.h"

static bool init_shell(shell_t *shell, char **env)
{
    shell->last_status = 0;
    shell->env = my_copy_array_of_strings(env);
    if (!shell->env)
        return false;
    return true;
}

static void shell_destroy(shell_t *shell)
{
    my_free_array_of_strings(shell->env);
}

int shell_run(char **env)
{
    shell_t shell;

    if (!init_shell(&shell, env)) {
        my_puterr("memory: couldn't allocate memory for the shell\n");
        return ERROR;
    }
    my_show_word_array(shell.env);
    shell_destroy(&shell);
    return SUCCESS;
}
