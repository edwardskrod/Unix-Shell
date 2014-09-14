#include <stddef.h> /* NULL */
#include "program.h"

/* The following function is the equivalent of C++'s constructor */
Program * theProgram( ){

	Program * program = (Program * )malloc( sizeof( Program ) );

	program->name = NULL;
	program->argc = 0;

	for (int i = 0; i < 51; ++i ) {
		program->argv[i] = NULL;
	}
		return program;
}