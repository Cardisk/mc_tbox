//
// Created by Matteo Cardinaletti on 01/02/23.
//

#ifndef MC_TBOX_MC_LINKED_LIST_H
#define MC_TBOX_MC_LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

/// Classical implementation of a linked list
typedef struct mc_l_list {
    void *value;               // generic value
    struct mc_l_list *next;    // pointer to the next element
} mc_l_list;

/// Initialize a new linked list node
/// \param value value
/// \return a new node
mc_l_list *mc_l_init(void *value) {
    // creating a new list
    mc_l_list *list = malloc(sizeof(mc_l_list));

    // storing a value inside the variable
    list->value = value;

    // make this node to point NULL
    list->next = NULL;

    // return the new list
    return list;
}

/// Add a new element in the first pos. inside the list
/// \param list list
/// \param value value
/// \return true if done, false otherwise
bool mc_l_head_insert(mc_l_list **list, void *value) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // creating a new node
    mc_l_list *new_node = mc_l_init(value);

    // make the new node to point to the old head
    new_node->next = *list;

    // updating the head
    *list = new_node;

    // everything is fine, success
    return true;
}

/// Add a new element in the last pos. inside the list
/// \param list list
/// \param value value
/// \return true if done, false otherwise
bool mc_l_tail_insert(mc_l_list **list, void *value) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // creating a new node
    mc_l_list *new_node = mc_l_init(value);

    // storing a reference of the list
    mc_l_list *it = *list;
    // looping through the list
    while (it->next != NULL) it = it->next;

    // adding the new node to the list
    it->next = new_node;

    // everything is fine, success
    return true;
}

/// Remove the first element of the list
/// \param list list
/// \param container where to store the value
/// \return true if done, false otherwise
bool mc_l_pop_first(mc_l_list **list, void **container) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // storing the value inside the container
    *container = (*list)->value;

    // saving the first node
    mc_l_list *node = *list;
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
bool mc_l_pop_last(mc_l_list **list, void **container) {
    // if the list is NULL, exit
    if (!list) return false;
    if (!(*list)) return false;

    // storing a reference of the list
    mc_l_list *it = *list;
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

#endif //MC_TBOX_MC_LINKED_LIST_H
