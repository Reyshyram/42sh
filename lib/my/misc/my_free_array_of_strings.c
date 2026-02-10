/*
** EPITECH PROJECT, 2026
** my_free_array_of_strings.c
** File description:
** Free an array of strings
*/

#include <stdlib.h>

void my_free_array_of_strings(char **array)
{
    for (size_t i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}
