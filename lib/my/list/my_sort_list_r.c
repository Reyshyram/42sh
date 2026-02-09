/*
** EPITECH PROJECT, 2025
** my_sort_list_r.c
** File description:
** Sort a linked list, with an additional argument given to the comparator
*/

#include "my/list.h"

// Since fast advances 2 times faster than slow,
// when fast is the last node, slow is the middle one.
static linked_list_t *separate_in_half(linked_list_t *head)
{
    linked_list_t *fast = head->next;
    linked_list_t *slow = head;
    linked_list_t *middle_node = nullptr;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    middle_node = slow->next;
    slow->next = nullptr;
    return middle_node;
}

static linked_list_t *merge(linked_list_t *head, linked_list_t *middle,
    int (*cmp)(const void *, const void *, void *), void *arg)
{
    linked_list_t start = {0};
    linked_list_t *tmp = &start;

    while (head && middle) {
        if (cmp(head->data, middle->data, arg) <= 0) {
            tmp->next = head;
            head = head->next;
        } else {
            tmp->next = middle;
            middle = middle->next;
        }
        tmp = tmp->next;
    }
    if (head)
        tmp->next = head;
    else if (middle)
        tmp->next = middle;
    return start.next;
}

// Split in half until only one node, and then reconstruct the list with
// sorted elements
linked_list_t *my_sort_list_r(linked_list_t *head,
    int (*cmp)(const void *, const void *, void *), void *arg)
{
    linked_list_t *middle = nullptr;

    if (!head || !head->next)
        return head;
    middle = separate_in_half(head);
    head = my_sort_list_r(head, cmp, arg);
    middle = my_sort_list_r(middle, cmp, arg);
    return merge(head, middle, cmp, arg);
}
