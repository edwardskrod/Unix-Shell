#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stddef.h> /* NULL */
#include "handleInput.h"
#include <stdlib.h>

TokenList* storeInput( ) {

  TokenList * tokenList = malloc(sizeof(TokenList));
  
  tokenList->parseStorage = (char**)malloc( sizeof(char*) * MAX_TOKENS);
  
  int j = 0;
  while (j < MAX_CHARS ) {

    tokenList->parseStorage[j] = (char*)malloc( sizeof(char) * MAX_CHARS);
    strcpy(tokenList->parseStorage[j], "");
    j++;
  }
  
  tokenList->count = 0;
  char *token; 

  char text[255];
    
  if ( fgets(text, sizeof text, stdin) != NULL ){

    char *newline = strchr(text, '\n'); /* search for newline character */
      if ( newline != NULL ) {
          *newline = '\0';            /* overwrite trailing newline */
        }  
  }
  char s[2] = " ";  // may need to add a NULL terminator

  /* get the first token */
  token = strtok(text, s);    

  /* walk through other tokens */
  while( token != NULL ) {
  
  strcpy(tokenList->parseStorage[tokenList->count], token);

    tokenList->count = tokenList->count + 1;
    token = strtok(NULL, s);

  }
 
  tokenList->parseStorage[tokenList->count] = NULL;

  return tokenList;
}