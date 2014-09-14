/**
 * posixVars
 * Description: Many Linux systems define the sizes for host name, path 
 * name, etc. in a file called posix1_lim.h.   If at all possible, 
 * we wanted to use these sizes in our shell.  However, in the case 
 * that these sizes are not defined, we needed to define them ourselves 
 * in the posixVars.h header file.  We also defined a few global variables,
 * such as the current working directory and previous working directory 
 * here as well.
 * Reference:  http://linux.die.net/man/3/sysconf  
 */
#pragma once

/* Linprog defines _POSIX_HOST_NAME_MAX as 255.  */
#ifndef HOST_NAME_MAX
  #ifdef _POSIX_HOST_NAME_MAX
    #define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
  #else 
    #define HOST_NAME_MAX 255
  #endif
#endif

/* Linprog defines _POSIX_LOGIN_NAME_MAX as 9. */
#ifndef LOGIN_NAME_MAX
  #ifdef _POSIX_LOGIN_NAME_MAX
    #define LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX
  #else
    #define LOGIN_NAME_MAX 9
  #endif
#endif

/* Linprog defines _POSIX_LOGIN_NAME_MAX as 255. */
#ifndef PATH_MAX
  #ifdef _POSIX_PATH_MAX
    #define PATH_MAX _POSIX_PATH_MAX
  #else
    #define PATH_MAX 255
  #endif
#endif

/** Global Variables **/
/** ProgramStatus:  tracks the status of the Program
*   Continue - continue to run the program
*   Exit - Exit the program before the next iteration
*   Error - An Error was detected.  Exit with Error status 
*/
enum ProgramStatus {
  CONTINUE,
  EXIT,
  ERROR
};
typedef enum ProgramStatus ProgramStatus;

ProgramStatus status;
char cwd[ PATH_MAX + 1 ]; // cwd: current working directory
char pwd[ PATH_MAX + 1]; // pwd: previous working directory

