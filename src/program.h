#pragma once

#include <malloc.h>  /* malloc */
#include <stddef.h> /* NULL */
#include "posixVars.h"

/*   Defines a Program       */

struct Program {

	char *name;
	char *argv[50];  // argv is going to be an array of
					// arguments passed to a particular program
					// We are limiting it to 50
	int argc;		// argc holds the number of args, including the name

	/*   We need to leave room for a number of other variables such
	as a pointer to the next program after a pipe 
	We also need to define the standard in and out (STDIN_FILENO, STDOUT_FILENO)

	*/
	
};

// typedef the struct so that anytime we type Program, 
// the compiler reads "struct Program"
typedef struct Program Program;

/*  Constructor declaration     */
Program * theProgram( );