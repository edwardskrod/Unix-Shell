
#include <string.h> /* string funcs */
#include <unistd.h> /* fork(), execv() */
#include <sys/wait.h> /* waitpid() */
#include <stdio.h> /* printf() */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stddef.h> /* NULL */
#include "posixVars.h"
#include "handleInput.h"


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

// cwd: current working directory
// pwd: previous working directory
char cwd[ PATH_MAX + 1 ];
char pwd[ PATH_MAX + 1];

void handleCommand(TokenList*);