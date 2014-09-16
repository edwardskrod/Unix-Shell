/**
 * program
 * Description: Defines a program and instantiates it with default
 * values upon creation.  Used by handleCommand.c when the user 
 * input is not a built-in but rather an executable.
 * STDIN_FILENO & STDOUT_FILENO are default standard input/output file descriptors
 */

#include <stddef.h> /* NULL */
#include "program.h"

Program * theProgram( ){

	Program * program = (Program * )malloc( sizeof( Program ) );

	program->name = NULL;
	program->argc = 0;
	program->redirectResource = NULL;
	program->redirect = DEFAULT;
	program->next = NULL;
	program->in = STDIN_FILENO;     // 0
	program->out = STDOUT_FILENO;   // 1

	for (int i = 0; i < 51; ++i ) {
		program->argv[i] = NULL;
	}
		return program;
}