//
// Created by Matteo Cardinaletti on 24/01/23.
//

#ifndef MC_TBOX_MC_UNIT_TEST_H
#define MC_TBOX_MC_UNIT_TEST_H

#include <stdio.h>
#include <string.h>

/// No-operation macro
#define NOOP ((void) 0)

/// Max test cases that can be registered
#define MC_MAX_TEST_CASES 1024

/// Text colors
enum mc_console_colors {
    MC_COLOR_DEFAULT = 0,
    MC_COLOR_FAIL = 31,
    MC_COLOR_SUCCESS = 32,
    MC_COLOR_TEST = 34
};

/// Change the console text color
/// \param color color from the enum list
void mc_set_console_color(enum mc_console_colors color) {
    printf("\033[0;%dm", color);
}

/// Print an assertion error
/// \param assertion assertion
/// \param filename __FILE__
/// \param line __LINE__
void mc_print_assertion(const char *assertion, const char *filename, size_t line) {
    mc_set_console_color(MC_COLOR_FAIL);
    printf("%s : %zu -> %s\n", filename, line, assertion);
    mc_set_console_color(MC_COLOR_DEFAULT);
}

/// Custom assert macro
#define mc_assert(_VAL) (_VAL) ? NOOP : mc_print_assertion(#_VAL, __FILE_NAME__, __LINE__)

/// Test case info
typedef struct mc_test_case {
    const char *name;

    void (*function)(void);
} mc_test_case;

/// List of all known test cases
static mc_test_case mc_test_cases[MC_MAX_TEST_CASES];
/// Number of test cases registered
static int mc_test_cases_num = 0;

/// Macro to register a new test case
#define mc_test_register(_FUNC) \
    do { \
        if (mc_test_cases_num > 1024) mc_print_assertion("Test cases number exceeded.", __FILE__, __LINE__); \
        mc_test_case *t_case = &mc_test_cases[mc_test_cases_num++]; \
        t_case->name = #_FUNC; \
        t_case->function = _FUNC;\
    } while(0)

/// Macro to execute all the test cases
#define mc_test_exec_all() \
    do { \
        for (int i = 0; i < mc_test_cases_num; ++i) { \
            mc_test_cases[i].function(); \
        } \
    } while(0)

/// Macro to execute a specific test case (_NAME must be a string)
#define mc_test_exec(_NAME) \
    do { \
        for (int i = 0; i < mc_test_cases_num; ++i) { \
            if (strcmp(_NAME, mc_test_cases[i].name) == 0) { \
                mc_test_cases[i].function(); \
                break; \
            } \
        } \
    } while(0)

#endif //MC_TBOX_MC_UNIT_TEST_H
