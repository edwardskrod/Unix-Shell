/**
 * program
 * Description: Defines a program and instantiates it with default
 * values upon creation.  Used by handleCommand.c when the user 
 * input is not a built-in but rather an executable.
 */

#include <stddef.h> /* NULL */
#include "program.h"

Program * theProgram( ){

	Program * program = (Program * )malloc( sizeof( Program ) );

	program->name = NULL;
	program->argc = 0;

	for (int i = 0; i < 51; ++i ) {
		program->argv[i] = NULL;
	}
		return program;
}