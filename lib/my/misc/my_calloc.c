/*
** EPITECH PROJECT, 2025
** my_calloc
** File description:
** Reproduce calloc behavior
*/

#include <stdlib.h>

void *my_calloc(size_t amount_of_elements, size_t size_of_element)
{
    void *new_malloc = malloc(size_of_element * amount_of_elements);

    if (!new_malloc)
        return nullptr;
    for (size_t i = 0; i < size_of_element * amount_of_elements; i++)
        ((unsigned char *) new_malloc)[i] = 0;
    return new_malloc;
}
