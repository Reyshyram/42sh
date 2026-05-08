/*
** EPITECH PROJECT, 2026
** wait_for_subprocess.c
** File description:
** Wait for subprocess and get status
*/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "my/misc.h"

#include "executer.h"

/*************************************
* The print_signal_message function prints the signal for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*   @param -> int status, an integer of the status
*************************************/
static void print_signal_message(int status)
{
    int signal = WTERMSIG(status);

    if (signal == SIGPIPE || signal == SIGINT)
        return;
    if (signal == SIGSEGV)
        fprintf(stderr, "Segmentation fault");
    else if (signal == SIGFPE)
        fprintf(stderr, "Floating exception");
    else
        fprintf(stderr, "%s", strsignal(signal));
    if (WCOREDUMP(status))
        fprintf(stderr, " (core dumped)");
    fprintf(stderr, "\n");
}

/*************************************
* The wait_for_subprocess function waits for the subprocess for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
* /!\ Add + 128 to follow the convention that the process
* /!\ was killed by a signal.
*
*   @param -> pid_t pid, structure found in include/pid.h
*   @return -> an integer, either a success or an error
*************************************/
int wait_for_subprocess(pid_t pid)
{
    int status = 0;

    do {
        if (waitpid(pid, &status, 0) == -1) {
            fprintf(stderr, "waitpid: %s.\n", strerror(errno));
            return ERROR;
        }
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        if (WIFSIGNALED(status)) {
            print_signal_message(status);
            return WTERMSIG(status) + 128;
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    return ERROR;
}
