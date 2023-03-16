//
// Created by Matteo Cardinaletti on 01/02/23.
//

#ifndef MC_TBOX_MC_STRETCHY_BUFFER_H
#define MC_TBOX_MC_STRETCHY_BUFFER_H

#include <stdlib.h>
#include <stdbool.h>

/// This struct represent the header of the buffer
typedef struct buffer_h {
    size_t size;            // the very first empty space of the array
    size_t capacity;        // how many items can be stored into the buffer
} mc_buffer_h;

/// Macro to create a generic buffer (it basically does the same thing as c but with a more oob approach)
#define mc_s_buffer(T) T*

/// It returns the header of the buffer
#define mc_buffer_header(_BUF) (((mc_buffer_h *) (_BUF)) - 1)

/// It returns the size of the buffer (number of elements)
#define mc_buffer_size(_BUF) ((_BUF) ? (mc_buffer_header(_BUF))->size : 0)
/// It returns the capacity of the buffer
#define mc_buffer_capacity(_BUF) ((_BUF) ? (mc_buffer_header(_BUF))->capacity : 0)

/// It returns the pointer to the first empty element
# define mc_buffer_get_ptr(_BUF) (mc_buffer_grow(_BUF), &((_BUF)[mc_buffer_header(_BUF)->size]))
/// It allows to push an element inside the buffer
#define mc_buffer_push(_BUF, _VAL) ((*(mc_buffer_get_ptr(_BUF)) = (_VAL)), (mc_buffer_header(_BUF))->size++)

/// It clears the buffer (reset the first empty space to 0)
#define mc_buffer_clear(_BUF) ((_BUF) ? ((mc_buffer_header(_BUF))->size = 0) : 0)
/// It frees the buffer memory and it sets the buffer pointer to NULL
#define mc_buffer_free(_BUF) (((_BUF) ? free(mc_buffer_header(_BUF)) : 0), (_BUF) = NULL)

/// If statement to check if a pointer is NULL
#define mc_check_ptr(_PTR) if (!(_PTR)) { free(_PTR); return; }
/// It resizes the buffer to store new data
static void mc_buffer_resize(void **buffer, size_t val_size) {
    // dumb method to determine the new capacity
    size_t new_capacity = mc_buffer_capacity(*buffer) <= 10 ? mc_buffer_capacity(*buffer) * 2 : mc_buffer_capacity(*buffer) * 0.5;
    new_capacity += (mc_buffer_capacity(*buffer) + 1);

    // numbers of bytes to allocate
    size_t bytes = sizeof(mc_buffer_h) + (val_size * new_capacity);

    // new buffer_h pointer
    mc_buffer_h* tmp = NULL;
    if (*buffer) {
        // if the buffer passed is not NULL, reallocate it
        tmp = (mc_buffer_h*) realloc(mc_buffer_header(*buffer), bytes);
        mc_check_ptr(tmp)
    } else {
        // if the buffer passed is NULL, allocate it
        tmp = (mc_buffer_h*) malloc(bytes);
        mc_check_ptr(tmp)
        tmp->size = 0;
    }

    tmp->capacity = new_capacity;

    // set the buffer passed to the new pointer + 1 (the first item of the array, ignoring the header)
    *buffer = tmp + 1;
}

/// It checks whether or not the buffer needs to grow
#define mc_buffer_grow(_BUF) (((mc_buffer_size(_BUF)) == (mc_buffer_capacity(_BUF))) ? mc_buffer_resize(((void**)&(_BUF)), sizeof(*(_BUF))) : 0)

#endif //MC_TBOX_MC_STRETCHY_BUFFER_H
