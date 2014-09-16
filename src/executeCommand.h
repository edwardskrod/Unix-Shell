#pragma once

#include <string.h> /* string funcs */
#include <unistd.h> /* fork(), execv() */
#include <sys/wait.h> /* waitpid() */
#include <stdio.h> /* printf() */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stddef.h> /* NULL */
#include "posixVars.h"
#include "handleInput.h"
#include "program.h"
#include "handleCommand.h"
#include "tokenize.h"   

void ioacct( pid_t p );
void executeCommand(TokenList * tList, Program * p, int isIoacct, 
					char ** parsedPath, int isBackgroundProgram);
void execute( char * name, char ** args , int i, int j );
char * getFinalPath( char ** parsedPath, TokenList * tList );