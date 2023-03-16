//
// Created by Matteo Cardinaletti on 20/01/23.
//

#ifndef MC_TBOX_MC_ERROR_HANDLER_H
#define MC_TBOX_MC_ERROR_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <errno.h>

/// Jump buffer to emulate TRY - CATCH block
static jmp_buf mc_jmp_buffer;

/// Emulates the TRY clause
#define MC_TRY if ((mc_jmp_value = setjmp(mc_jmp_buffer)) == 0)
/// Emulates the CATCH clause (with specific exception)
#define MC_CATCH(_VAL) else if (mc_jmp_value == _VAL)
/// Emulates a generic CATCH clause
#define MC_CATCH_ALL else
/// Emulates the THROW function
#define MC_THROW(_VAL) longjmp(mc_jmp_buffer, _VAL)

/// Pretty printing for system error handling
#define mc_try_errno(_VAL) ({ int __value = (_VAL); (__value == -1 ? \
            ({fprintf(stderr, "ERROR: (" __FILE__ " : %d ) -- %s\n", __LINE__, strerror(errno)); exit(-1); -1;}) : __value);})

/// Shortcut
typedef unsigned int mc_uint;

/// Custom errno value (no errors = 0)
mc_uint mc_errno = 0;

/// Error info structure
typedef struct mc_error_info {
    const int value;
    const char *const name;
    const char *const msg;
} mc_error_info;

/// An entry for the error table
#define MC_ENTRY(_VAL, _NAME, _MSG) {_VAL, _NAME, _MSG};

/// Error table
mc_error_info **mc_error_table = NULL;
/// Error table size
mc_uint mc_terr_size = 0;

/// Initialize the error table with a custom one
/// \param error_table custom error table
/// \param size error table size
void mc_init_error_table(mc_error_info error_table[], mc_uint size) {
    // assign the custom error table
    *mc_error_table = error_table;
    // assign the custom error table size
    mc_terr_size = size;
}

/// Retrieve a short message for the corresponding error
/// \param error_value error value contained inside mc_errno
/// \return a short message
const char *mc_strerror(int error_value) {
    // if error table is NULL, or the error value is out of bounds, exit
    if (!mc_error_table || error_value < 0 || error_value > mc_terr_size) return NULL;

    // if this constant is declared, it means that some custom errno codes can overlap the system ones, skip this
#ifndef MC_ERRNO_SYS_OVERLAP
    // if custom errno doesn't overlap the system one, check also for it
    if (error_value > 0 && error_value <= 131) return strerror(error_value);
#endif

    // if the table contains ordered values return the relative msg
    if (mc_error_table[error_value - 1] && mc_error_table[error_value - 1]->value == error_value)
        return mc_error_table[error_value - 1]->msg;

    // if the table isn't ordered, search for the corresponding error
    for (int i = 0; i < mc_terr_size; ++i) {
        // if the error is found, return the msg
        if (mc_error_table[i] && mc_error_table[i]->value == error_value) return mc_error_table[i]->msg;
    }

    // if the code arrives here, no error code found, exit
    return NULL;
}

/// Print out to the standard error stream and exit with exit(int status) function
/// \param text some text (if not required, set it to NULL)
/// \param exit_code an exit code
void mc_err_and_die(const char *text, int exit_code) {
    // execute only one time the strlen function, if text is defined
    size_t text_len = (text ? strlen(text) : 0);

    // check for the correct msg error
    if (mc_errno == 0 && text_len == 0) fprintf(stderr, "ERROR: An error occurred during the execution.\n");
    else if (mc_errno == 0 && text_len > 0) fprintf(stderr, "ERROR - %s\n", text);
    else if (mc_errno != 0 && text_len == 0) fprintf(stderr, "ERROR: %s\n", mc_strerror((int) mc_errno));
    else fprintf(stderr, "ERROR - %s: %s\n", text, mc_strerror((int) mc_errno));

    // exit from the program with the given exit code
    exit(exit_code);
}
#endif //MC_TBOX_MC_ERROR_HANDLER_H
