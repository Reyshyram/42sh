/*
** EPITECH PROJECT, 2026
** my_memset.c
** File description:
** my_memset.c
*/

#include <stddef.h>
#include <stdint.h>

void *my_memset(void *s, int c, size_t n)
{
    uint8_t *ptr = s;

    for (size_t i = 0; i < n; i++)
        ptr[i] = c;
    return s;
}
