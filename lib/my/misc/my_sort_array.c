/*
** EPITECH PROJECT, 2025
** my_sort_array
** File description:
** Sort an array using a given comparator
*/

#include <stddef.h>

#include "my/misc.h"

static void swap(void *a, void *b, size_t size)
{
    char temp[size];

    my_memcpy(temp, b, size);
    my_memcpy(b, a, size);
    my_memcpy(a, temp, size);
}

static int partition(void *array, struct quicksort_elements *elements,
    const struct quicksort_position *position,
    int (*cmp)(const void *, const void *))
{
    void *pivot = array + position->end * elements->size;
    int partition_index = position->start;

    for (int i = position->start; i < position->end; i++) {
        if (cmp(pivot, array + i * elements->size) > 0) {
            swap(array + i * elements->size,
                array + partition_index * elements->size, elements->size);
            partition_index++;
        }
    }
    swap(array + position->end * elements->size,
        array + partition_index * elements->size, elements->size);
    return partition_index;
}

static void quick_sort(void *array, struct quicksort_elements *elements,
    struct quicksort_position *position,
    int (*cmp)(const void *, const void *))
{
    int partition_index = 0;

    if (position->start < position->end) {
        partition_index = partition(array, elements, position, cmp);
        quick_sort(array, elements,
            &(struct quicksort_position) {position->start,
                partition_index - 1},
            cmp);
        quick_sort(array, elements,
            &(struct quicksort_position) {partition_index + 1, position->end},
            cmp);
    }
}

void my_sort_array(void *array, size_t nb_elements, size_t element_size,
    int (*cmp)(const void *, const void *))
{
    struct quicksort_elements elements = {nb_elements, element_size};
    struct quicksort_position position = {0, (int) nb_elements - 1};

    quick_sort(array, &elements, &position, cmp);
}
