#pragma once

#include <malloc.h>  /* malloc */
#include <stddef.h> /* NULL */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "posixVars.h"

enum Redirection {
	IN,
	OUT,
	DEFAULT
};
typedef enum Redirection Redirection;

/*   Defines a Program       */
struct Program {

	char *name;
	char *argv[50];  // argv is going to be an array of
					// arguments passed to a particular program
					// We are limiting it to 50
	int argc;		// argc holds the number of args, including the name

	Redirection redirect;
	struct Program *next;  // points to the next program
	

	
};

// typedef the struct so that anytime we type Program, 
// the compiler reads "struct Program"
typedef struct Program Program;

/*  Constructor declaration     */
Program * theProgram( );



