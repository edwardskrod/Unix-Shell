#pragma once
#include <malloc.h>  /* malloc */
#include <stddef.h> /* NULL */
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "posixVars.h"
#include "program.h"
#include "handleInput.h"


/*  Defines a list of programs that make up a command */
struct CommandList {

	Program * program;
	int numberOfPrograms;

};
typedef struct CommandList CommandList;
CommandList * theCommandList();
void parseCommandList(CommandList * c, TokenList * t);
