/*
** EPITECH PROJECT, 2026
** empty_stdin
** File description:
** Empty the stdin
*/

#include <stdio.h>
#include <stdlib.h>

/*************************************
* The empty_stdin function empties the stdin for 42sh.
* It respects the Banana and epiclang coding styles from Epitech.
*
*************************************/
void empty_stdin(void)
{
    char *line = nullptr;
    size_t size = 0;

    while (true)
        if (getline(&line, &size, stdin) == -1)
            break;
    free(line);
}
