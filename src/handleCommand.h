#pragma once

#include <string.h> /* string funcs */
#include <unistd.h> /* fork(), execv() */
#include <sys/wait.h> /* waitpid() */
#include <stdio.h> /* printf() */
#include <stdlib.h> /* EXIT_SUCCESS */
#include <stddef.h> /* NULL */
#include "posixVars.h"
#include "handleInput.h"

void handleCommand(TokenList*);