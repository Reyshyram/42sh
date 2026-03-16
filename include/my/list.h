/*
** EPITECH PROJECT, 2025
** my/list.h
** File description:
** Header file for linked lists
*/

#ifndef MY_LIST_H
// clang-format off
    #define MY_LIST_H

    #include <stddef.h>
// clang-format on

typedef struct linked_list {
    void *data;
    struct linked_list *next;
} linked_list_t;

bool my_add_to_list(linked_list_t **head, void *data);
bool my_add_to_list_end(linked_list_t **head, void *data);
size_t my_list_length(linked_list_t *head);
linked_list_t *my_sort_list_r(linked_list_t *head,
    int (*cmp)(const void *, const void *, void *), void *arg);
linked_list_t *my_sort_list(linked_list_t *head,
    int (*cmp)(const void *, const void *));
void my_free_list(linked_list_t *head, void (*free_data)(void *));
linked_list_t *my_delete_node(linked_list_t **head, linked_list_t *to_delete,
    linked_list_t *prev, void (*free_data)(void *));

#endif /* MY_LIST_H */
