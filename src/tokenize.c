/** 
 * A brief demonstration of using strtok_r correctly to parse the PATH.
 */

// Use SUS/UNIX source versions
// http://pubs.opengroup.org/onlinepubs/9699919799/functions/V2_chap02.html#tag_15_02_01_01
#define _XOPEN_SOURCE 700
#define SIZE 100
#include "tokenize.h"

// strlen()
// http://pubs.opengroup.org/onlinepubs/9699919799/functions/strlen.html

/* TO DO:
   PATHNAME IS UNUSED 
*/
   
char ** pathParser(char * pathName)
{
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

printf("PATH: %s\n", getenv("PATH"));
printf("PATH: %s\n\n", path);

// Iterate through each token.
// Notice how saveptr outputs fewer characters after each call to strtok_r(). 
for(char *token = strtok_r(path, delim, &saveptr);
    token != NULL;
    token = strtok_r(NULL, delim, &saveptr)) {
  printf("saveptr: %s\n", saveptr);
  printf("%s\n", token);
  strList[i] = token;
  printf("\n");
  printf("Holder is this: %s \n", strList[i]);
  i++;
}

return strList;
}
