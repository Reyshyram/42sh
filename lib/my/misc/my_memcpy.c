/*
** EPITECH PROJECT, 2025
** my_memcpy
** File description:
** Copy a portion of memory
*/

#include <stddef.h>

void *my_memcpy(void *dest, const void *src, size_t len)
{
    for (size_t i = 0; i < len; i++)
        ((char *) dest)[i] = ((char *) src)[i];
    return dest;
}
