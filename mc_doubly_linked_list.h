//
// Created by Matteo Cardinaletti on 02/02/23.
//

#ifndef MC_TBOX_MC_DOUBLY_LINKED_LIST_H
#define MC_TBOX_MC_DOUBLY_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct mc_dl_list {
    void *value;
    struct mc_dl_list *prev;
    struct mc_dl_list *next;
} mc_dl_list;

/// Initialize a new linked list node
/// \param value value
/// \return a new node
mc_dl_list *mc_dl_init(void *value) {
    // creating a new list
    mc_dl_list *list = malloc(sizeof(mc_dl_list));

    // storing a value inside the variable
    list->value = value;

    // make this node to point NULL
    list->prev = NULL;
    list->next = NULL;

    // return the new list
    return list;
}

/// Add a new element in the first pos. inside the list
/// \param list list
/// \param value value
/// \return true if done, false otherwise
bool mc_dl_head_insert(mc_dl_list **list, void *value) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // creating a new node
    mc_dl_list *new_node = mc_dl_init(value);

    // make the new node to point to the old head
    new_node->next = *list;
    (*list)->prev = new_node;

    // updating the head
    *list = new_node;

    // everything is fine, success
    return true;
}

/// Add a new element in the last pos. inside the list
/// \param list list
/// \param value value
/// \return true if done, false otherwise
bool mc_dl_tail_insert(mc_dl_list **list, void *value) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // creating a new node
    mc_dl_list *new_node = mc_dl_init(value);

    // storing a reference of the list
    mc_dl_list *it = *list;
    // looping through the list
    while (it->next != NULL) it = it->next;

    // adding the new node to the list
    it->next = new_node;
    new_node->prev = it;

    // everything is fine, success
    return true;
}

/// Remove the first element of the list
/// \param list list
/// \param container where to store the value
/// \return true if done, false otherwise
bool mc_dl_pop_first(mc_dl_list **list, void **container) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // storing the value inside the container
    *container = (*list)->value;

    // saving the first node
    mc_dl_list *node = *list;
    // update the head
    *list = (*list)->next;
    // freeing the memory
    free(node);

    // everything is fine, success
    return true;
}

/// Remove the last element of the list
/// \param list list
/// \param container where to store the value
/// \return true if done, false otherwise
bool mc_dl_pop_last(mc_dl_list **list, void **container) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // storing a reference of the list
    mc_dl_list *it = *list;
    // looping through the list
    while (!it->next && !it->next->next) it = it->next;

    // storing the value inside the container
    *container = it->next->value;

    // freeing the node
    free(it->next);
    // set it to NULL
    it->next = NULL;

    // everything is fine, success
    return true;
}

#endif //MC_TBOX_MC_DOUBLY_LINKED_LIST_H
