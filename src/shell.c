/*
** EPITECH PROJECT, 2026
** shell.c
** File description:
** shell.c
*/

#include <stdlib.h>
#include <unistd.h>

#include "my/io.h"
#include "my/misc.h"

#include "shell.h"

static bool init_shell(shell_t *shell, char **env)
{
    shell->last_status = 0;
    shell->interactive = isatty(STDIN_FILENO);
    shell->env = my_copy_word_array(env);
    if (!shell->env)
        return false;
    return true;
}

static void shell_destroy(shell_t *shell)
{
    my_free_word_array(shell->env);
}

int shell_run(char **env)
{
    shell_t shell;
    char *line = nullptr;

    if (!init_shell(&shell, env)) {
        my_puterr("memory: couldn't allocate memory for the shell\n");
        return ERROR;
    }
    while (true) {
        line = read_input(shell.interactive);
        if (!line)
            break;
        free(line);
    }
    shell_destroy(&shell);
    return shell.last_status;
}
