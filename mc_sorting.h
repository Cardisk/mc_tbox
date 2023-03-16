//
// Created by Matteo Cardinaletti on 09/02/23.
//

#ifndef MC_TBOX_MC_SORTING_H
#define MC_TBOX_MC_SORTING_H

#include <string.h>
#include <stdlib.h>

void void_swap(void *a, void *b, size_t size) {
    void *tmp = malloc(size);
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
    free(tmp);
}

// Selection sort
void selection_sort(void *array[], const int array_size, int (*is_equal)(void *a, void *b), const size_t item_size) {
    int min;

    for (int i = 0; i < array_size - 1; ++i) {
        // Assuming the index of the min. value is the current pos.
        min = i;
        // Find the index of the min. value
        for (int j = i + 1; j < array_size; ++j) {
            if (is_equal(array[j], array[min]) < 0) min = j; // if < 0, first is less
        }

        // Switching the min. value with the current one
        void_swap(array[min], array[i], item_size);
//        void *tmp = array[min];
//        array[min] = array[i];
//        array[i] = tmp;
    }
}

// Bubble sort
void bubble_sort(void *array[], const int array_size, int (*is_equal)(void *a, void *b), const size_t item_size) {
    // Looping through all the elements until LEN - 2
    for (int i = 0; i < array_size - 1; ++i) {
        // Looping through all the elements until LEN - i - 1
        for (int j = 0; j < array_size - i - 1; ++j) {
            // Checking if the current value is greater than its next
            if (is_equal(array[j], array[j + 1]) > 0) {
                // Switching the values
                void_swap(array[j], array[j + 1], item_size);
//                int tmp = array[j];
//                array[j] = array[j + 1];
//                array[j + 1] = tmp;
            }
        }
    }
}

// Merge sort
void merge(void *array[], const int array_size, int (*is_equal)(void *a, void *b),
           int left, int middle, int right) {
    // Support variables
    int i = left, j = middle + 1, k = 0;
    // Temporary array
    void **t_arr = malloc(sizeof(int) * array_size);

    // Order the two side of the array
    while (i <= middle && j <= right) {
        t_arr[k] = (is_equal(array[i], array[j]) < 0 ? array[i] : array[j]);
        (is_equal(array[i], array[j]) < 0 ? i++ : j++);
        k++;
    }

    // If there is something left inside the right array, put it inside the temp. one
    while (i <= middle) {
        t_arr[k] = array[i];
        i++;
        k++;
    }

    // If there is something left inside the left array, put it inside the temp. one
    while (j <= right) {
        t_arr[k] = array[j];
        j++;
        k++;
    }

    // Now copy the ordered result from the temp. array to the actual one
    for (int x = left; x <= right; ++x) {
        array[x] = t_arr[x - left];
    }

    free(t_arr);
}

void merge_sort(void *array[], const int array_size, int (*is_equal)(void *a, void *b),
                int left, int right) {
    // If the two indexes are equals the array is divided into singular pieces, it can now be merged
    if (left >= right) return;

    // Establish the middle point to split the array
    int middle = (int) ((left + right) / 2);
    // Call recursively the function with the left side of the array
    merge_sort(array, array_size, is_equal, left, middle);
    // Call recursively the function with the right side of the array
    merge_sort(array, array_size, is_equal, middle + 1, right);
    // Merge both the sides
    merge(array, array_size, is_equal, left, middle, right);
}

// Quick sort
void quick_sort(void *array[], const int array_size, int (*is_equal)(void *a, void *b), const size_t item_size,
                int left, int right) {
    // If the left index is equals to the right one, exit
    if (left == right) return;

    // Assuming the pivot as the first position
    int pivot = left;
    // Storing the length of the array or subarray
    int len = right;
//    int tmp;

    // Looping until the condition is true
    while (left < right) {
        // Moving backwards the right index until the condition is true

        while (is_equal(array[pivot], array[right]) < 0 && left < right) right--;

        // Moving forward the left index until the condition is true
        while (is_equal(array[pivot], array[left]) >= 0 && left < right) left++;

        // If the two indexes are different switch the items
        if (left != right) {
            void_swap(array[left], array[right], item_size);
//            tmp = array[left];
//            array[left] = array[right];
//            array[right] = tmp;
        }
    }

    // If the pivot is equals to the left index, the array is sorted
    if (pivot == left) return;

    // Switching the pivot with the item into the left index position
    void_swap(array[left], array[pivot], item_size);
//    tmp = array[left];
//    array[left] = array[pivot];
//    array[pivot] = tmp;

    // Calling recursively the function with the left array and its bounds
    quick_sort(array, array_size, is_equal, item_size, pivot, left - 1);
    // Calling recursively the function with the right array and its bounds
    quick_sort(array, array_size, is_equal, item_size, left + 1, len);
}

#endif //MC_TBOX_MC_SORTING_H
