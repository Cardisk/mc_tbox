//
// Created by Matteo Cardinaletti on 09/02/23.
//

#ifndef MC_TBOX_MC_SEARCHING_H
#define MC_TBOX_MC_SEARCHING_H

#include <stdbool.h>
#include <math.h>

int sequential_search(void *array[], const int array_size, void *target, int (*is_equal)(void *a, void *b)) {
    // The array can be sorted or not, the research is done sequentially so nothing changes
    for (int i = 0; i < array_size; ++i) {
        // If the item at the current position is equals to the target, return the index
        if (is_equal(array[i], target) == 0) return i;
    }

    // If the element is not present inside the array, exit
    return -1;
}

int binary_search(void *array[], void *target, const int left, const int right, int (*is_equal)(void *a, void *b)) {
    // If the left bound is greater than the right one, the item is not present inside the array, exit
    if (left >= right) return -1;

    // Estimating the middle point of the array
    int middle = right - (right - left) / 2;

    // If the target is equals to the middle item, return the current pos.
    if (is_equal(array[middle], target) == 0) return middle;

    // If the target is less than the middle one, search inside the right part of the array
    if (is_equal(array[middle], target) > 0)        // if > 0, first is greater
        return binary_search(array, target, left, middle - 1, is_equal);
        // If the target is greater than the middle one, search inside the left part of the array
    else
        return binary_search(array, target, middle, right, is_equal);
}

int jump_search(void *array[], const int array_size, void *target, int (*is_equal)(void *a, void *b)) {
    // Estimating optimal jump
    int optimal_jump = (int) sqrt(array_size);

    int i = 0;
    // Jumping through the array until an item is greater than target
    while (i + optimal_jump <= array_size) {
        if (is_equal(array[i], target) < 0) i += optimal_jump;  // if < 0, first is less
        else break;
    }

    // Moving backwards inside the array until the item is found
    while(i >= 0) {
        if (is_equal(array[i], target) == 0) return i;
        i--;
    }

    // Target is not present inside the array, exits
    return -1;
}

#endif //MC_TBOX_MC_SEARCHING_H
