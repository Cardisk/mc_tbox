//
// Created by Matteo Cardinaletti on 01/02/23.
//

#ifndef MC_TBOX_MC_QUEUE_H
#define MC_TBOX_MC_QUEUE_H

#include "mc_linked_list.h"

/// Defining a queue as a special linked list
typedef mc_l_list mc_queue;

/// Initialize the queue
/// \param value value
/// \return a new queue
mc_queue *mc_q_init(void *value) {
    // calling the linked list init function
    return mc_l_init(value);
}

/// Push a value inside the queue
/// \param queue queue
/// \param value value
/// \return true if done, false otherwise
bool mc_q_push(mc_queue **queue, void *value) {
    // calling the head insert function
    return mc_l_head_insert(queue, value);
}

/// Pop a value from the queue
/// \param queue queue
/// \param container where to store the value
/// \return true if done, false otherwise
bool mc_q_pop(mc_queue **queue, void **container) {
    // calling the pop last function
    return mc_l_pop_last(queue, container);
}

#endif //MC_TBOX_MC_QUEUE_H
