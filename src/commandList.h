#pragma once

#include <malloc.h>  /* malloc */
#include <stddef.h> /* NULL */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "posixVars.h"


/*  Defines a list of programs that make up a command */
struct CommandList {

	Program * * program;
	int numberOfPrograms;

};
typedef struct CommandList CommandList;

