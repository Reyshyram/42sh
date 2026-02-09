/*
** EPITECH PROJECT, 2025
** my_realloc
** File description:
** Reproduce realloc behavior
*/

#include "my/misc.h"
#include <stdlib.h>

void *my_realloc(void *pointer, size_t old_size, size_t new_size)
{
    void *new_pointer = malloc(new_size);

    if (!new_pointer)
        return nullptr;
    if (pointer != nullptr)
        my_memcpy(new_pointer, pointer, old_size);
    free(pointer);
    return new_pointer;
}
