/*
** EPITECH PROJECT, 2026
** wait_for_subprocess.c
** File description:
** Wait for subprocess and get status
*/

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "my/io.h"
#include "my/misc.h"

#include "executer.h"

static void print_signal_message(int status)
{
    int signal = WTERMSIG(status);

    if (signal == SIGSEGV)
        my_puterr("Segmentation fault");
    else if (signal == SIGFPE)
        my_puterr("Floating exception");
    else
        my_puterr(strsignal(signal));
    if (WCOREDUMP(status))
        my_puterr(" (core dumped)");
    my_puterr("\n");
}

int wait_for_subprocess(pid_t pid)
{
    int status = 0;

    do {
        if (waitpid(pid, &status, 0) == -1) {
            my_dprintf(STDERR_FILENO, "waitpid: %s.\n", strerror(errno));
            return ERROR;
        }
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        if (WIFSIGNALED(status)) {
            print_signal_message(status);
            return status;
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ERROR;
}
