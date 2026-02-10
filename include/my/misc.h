/*
** EPITECH PROJECT, 2025
** my/misc.h
** File description:
** Misc functions that do not fit elsewhere
*/

#ifndef MY_MISC_H
// clang-format off
    #define MY_MISC_H

    #include <stddef.h>
    #define ERROR 84
    #define SUCCESS 0
// clang-format on

struct quicksort_elements {
    size_t count;
    size_t size;
};

struct quicksort_position {
    int start;
    int end;
};

void my_sort_array(void *array, size_t nb_elements, size_t element_size,
    int (*cmp)(const void *, const void *));

void *my_calloc(size_t amount_of_elements, size_t size_of_element);
void *my_realloc(void *pointer, size_t old_size, size_t new_size);
void *my_memcpy(void *dest, const void *src, size_t len);
void my_free_array_of_strings(char **array);
char **my_copy_array_of_strings(char **array);

#endif /* MY_MISC_H */
