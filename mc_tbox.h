//
// Created by Matteo Cardinaletti on 20/01/23.
//

#ifndef MC_TBOX_MC_TBOX_H
#define MC_TBOX_MC_TBOX_H

#include <string.h>

#ifdef MC_TBOX_ALL
    #define MC_ERROR_HANDLER
    #define MC_UNIT_TEST
    #define MC_FILE_HANDLER
    #define MC_LINKED_LIST
    #define MC_DOUBLY_LINKED_LIST
    #define MC_STACK
    #define MC_QUEUE
    #define MC_STRETCHY_BUFFER
    #define MC_HASH_TABLE
#endif

/// Transform the passed value into a string
#define mc_stringify(_VAL) #_VAL

/// Max function
#define mc_max_val(_A, _B) (_A) > (_B) ? (_A) : (_B)

/// Min function
#define mc_min_val(_A, _B) (_A) < (_B) ? (_A) : (_B)

/// Array size
#define mc_array_size(_ARR) _Generic(_ARR, char *: strlen(_ARR), default: sizeof(_ARR) / sizeof(*(_ARR)))

/// Swap two values
#define mc_swap(_A, _B) { _A = _A + _B; _B = _A - _B; _A = _A - _B; }

// ERROR HANDLER
#ifdef MC_ERROR_HANDLER
    #include "mc_error_handler.h"
#endif

// TEST API
#ifdef MC_UNIT_TEST
    #include "mc_unit_test.h"
#endif

// FILE HANDLER
#ifdef MC_FILE_HANDLER
    #include "mc_file_handler.h"
#endif

// DATA STRUCTURES

// - linked list
#ifdef MC_LINKED_LIST
    #include "mc_linked_list.h"
#endif

// - double linked list
#ifdef MC_DOUBLY_LINKED_LIST
    #include "mc_doubly_linked_list.h"
#endif

// - stack
#ifdef MC_STACK
    #include "mc_stack.h"
#endif

// - queue
#ifdef MC_QUEUE
    #include "mc_queue.h"
#endif

// - vector
#ifdef MC_STRETCHY_BUFFER
    #include "mc_stretchy_buffer.h"
#endif

// - hash map
#ifdef MC_HASH_TABLE
    #define MC_HM_IMPL
    #include "mc_hash_table.h"
#endif

// - tree

// - graphs

// ALGORITHMS

// - sorting algo

// - searching algo

#endif //MC_TBOX_MC_TBOX_H
