/*
** EPITECH PROJECT, 2026
** my_free_word_array.c
** File description:
** Free an array of strings
*/

#include <stdlib.h>

void my_free_word_array(char **array)
{
    if (!array)
        return;
    for (size_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
