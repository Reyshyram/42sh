/*
** EPITECH PROJECT, 2026
** empty_stdin
** File description:
** Empty the stdin
*/

#include <stdio.h>
#include <stdlib.h>

void empty_stdin(void)
{
    char *line = nullptr;
    size_t size = 0;

    while (true)
        if (getline(&line, &size, stdin) == -1)
            break;
    free(line);
}
