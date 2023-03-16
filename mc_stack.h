//
// Created by Matteo Cardinaletti on 01/02/23.
//

#ifndef MC_TBOX_MC_STACK_H
#define MC_TBOX_MC_STACK_H

#include "mc_linked_list.h"

/// Defining a stack as a special linked list
typedef mc_l_list mc_stack;

/// Initialize the stack
/// \param value value
/// \return the stack
mc_stack *mc_s_init(void *value) {
    // calling the init function
    return mc_l_init(value);
}

/// Push an element inside the stack
/// \param stack stack
/// \param value value
/// \return true if done, false otherwise
bool mc_s_push(mc_stack **stack, void *value) {
    // calling the head insert to add element on top of the stack
    return mc_l_head_insert(stack, value);
}

/// Pop a value from the stack
/// \param stack stack
/// \param container where to store the value
/// \return true if done, false otherwise
bool mc_s_pop(mc_stack **stack, void **container) {
    // calling the pop first function to remove the first element
    return mc_l_pop_first(stack, container);
}

#endif //MC_TBOX_MC_STACK_H
