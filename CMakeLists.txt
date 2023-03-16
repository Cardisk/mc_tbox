cmake_minimum_required(VERSION 3.23)
project(mc_tbox C)

set(CMAKE_C_STANDARD 23)

add_executable(mc_tbox main.c mc_tbox.h mc_error_handler.h mc_file_handler.h mc_unit_test.h mc_stretchy_buffer.h mc_hash_table.h mc_linked_list.h mc_stack.h mc_queue.h mc_doubly_linked_list.h mc_searching.h mc_sorting.h)
