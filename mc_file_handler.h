//
// Created by Matteo Cardinaletti on 23/01/23.
//

#ifndef MC_TBOX_MC_FILE_HANDLER_H
#define MC_TBOX_MC_FILE_HANDLER_H

#include <stdbool.h>

#include "mc_error_handler.h"

/// Perform an action over a file
/// \param file_path file path
/// \param mode opening mode
/// \param callback action to be performed
/// \return true if done, false otherwise
bool mc_do_some_on_file(const char *restrict file_path, const char *mode, bool (*callback)(FILE *file)) {
    // open the file with the given mode
    FILE *file = fopen(file_path, mode);
    // if file is NULL, exit
    if (!file) {
#ifndef MC_ERRNO_SYS_OVERLAP
        mc_errno = errno;
#endif
        return false;
    }

    // call the given function
    bool res = callback(file);

    // close the file and store the exit result
    int ret = fclose(file);
    // if something happened during while closing, set the error
    if (ret != 0) {
#ifndef MC_ERRNO_SYS_OVERLAP
        mc_errno = errno;
#endif
    }

    // return the outcome of the given function
    return res;
}

// TODO: Expand this "api" with other useful functions

#endif //MC_TBOX_MC_FILE_HANDLER_H
