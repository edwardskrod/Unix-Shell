/**
 * tokenize
 * Description: Receives the $PATH environment variable and 
 * tokenizes it based upon the ":" delimiter into an array of 
 * C strings.  We check this array for the location of an executable
 * in handleCommand.c
 * Reference:  Adapted from code written by Mark Stanovich,
 * http://ww2.cs.fsu.edu/~stanovic
 */

#include "tokenize.h"
char ** pathParser()
{

  /* MUST DEALLOCATE THIS MEMORY IN THE FUNCTION HANDLECOMMAND.C - DONE */
  char **strList = (char **)malloc(sizeof(char*) * SIZE);
  int i = 0;
  if (strList != NULL){
    for (i = 0; i < SIZE; i++){
      strList[i] = (char *)malloc(SIZE * sizeof(char) + 1);
      if (strList[i] != NULL){
	       sprintf(strList[i], "Foo%d", i);
      }
    }
  }
  i = 0;
const char *const delim = ":";
const size_t path_len = strlen(getenv("PATH")) + 1; // add 1 for NUL character (strlen does not include NUL character)
char path[path_len];
char *saveptr;

strncpy(path, getenv("PATH"), path_len);
path[path_len-1] = '\0';

// Iterate through each token.
// Notice how saveptr outputs fewer characters after each call to strtok_r(). 
for(char *token = strtok_r(path, delim, &saveptr);
    token != NULL;
    token = strtok_r(NULL, delim, &saveptr)) {
    strcpy(strList[i], token);
  i++;
}

return strList;
}
