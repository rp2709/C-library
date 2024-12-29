#ifndef STATUS_H
#define STATUS_H

#include "Types.h"

/**
 * Basic signification of a status, can (and should) be used as boolean value to check for operation success
 */
enum _short_status{_ERROR = 0,_OK,_WARNING};

/**
 * Return status object
 * Every new module, lib, project should create its own errors and warning if necessary
 * The ONLY ok status needed is OK
 */
typedef struct {
    enum _short_status success;
    const char * name;
    const char * description;
}status;

extern const status OK;
extern const status ERROR;
extern const status WARNING;

/**
 * Exits on an error or a warning and displays it
 * /!\ should always be used since warnings indicate bad logic
 * @param s status returned by a function
 */
void pedantic_assert(status s);

/**
 * Exits on an error
 * @param s status returned by a function
 */
void strong_assert(status s);

/**
 * Displays a status (success, name and description)
 * @param s status returned by a function
 */
void display_status(status s);

/**
 * Displays only errors
 * @param s status returned by a function
 */
void display_error(status s);

#endif //STATUS_H
