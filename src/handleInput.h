#pragma once

#define MAX_TOKENS 50
#define MAX_CHARS 50
typedef struct  {

  int count;
  char **parseStorage;

} TokenList;


TokenList *storeInput(  );




