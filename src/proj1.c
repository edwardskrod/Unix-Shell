#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include "posixVars.h"
#include "handleInput.h"
#include "handleCommand.h"


/*  Global variables / structs   */
typedef struct Total
{
  int pid;
  int directionToken;
  char ** argument;
  int background;
} Total;

/*  Function Declarations  */
void printPrompt(  );

int main() {

  TokenList * tList;
  ProgramStatus status = CONTINUE;
  getcwd(cwd, PATH_MAX);
  while (  status == CONTINUE  ) {

    printPrompt();

    tList = storeInput();

    handleCommand(tList);

    /*  free derp */
    free(tList);
 }


  return 0;
}

void printPrompt( )
/* Builds a string from the Current Working Directory, 
hostName and loginName and prints it to the console in the 
format <username>@<hostname>:<working_directory> $
 */
{
  char current[ PATH_MAX + 1 ];
  char hostName[ HOST_NAME_MAX + 1 ];
  char loginName[ LOGIN_NAME_MAX + 1 ];

  /* Get the Current Working Directory */
  getcwd( current, PATH_MAX );
  
  /* Get the hostname */
  gethostname( hostName, HOST_NAME_MAX );
  
  /* Get the loginName */
  getlogin_r( loginName, LOGIN_NAME_MAX );

  /* Make sure the strings are null terminated */
  current[PATH_MAX] = 0;
  hostName[ HOST_NAME_MAX ] = 0;
  loginName[ LOGIN_NAME_MAX ] = 0;

  fprintf( stdout, "%s@%s:%s $ \n", loginName, hostName, current );

  // flush stdout
  fflush( stdout );

}



/**********************  parseInput   ****************************/
/*
Total* parseInput( TokenList t  ) {

  int pipeCounter = 1;
  int i = 0;
  int j = 0;
  int increment = 0;

  for(i = 0; i < t.count; i++) {

      if(strcmp(t.parseStorage[i],"|") == 0 || 
        strcmp(t.parseStorage[i],">") == 0 || 
        strcmp(t.parseStorage[i],"<") == 0 || 
        strcmp(t.parseStorage[i], ">>") == 0) {
        
        pipeCounter++;    
      }
  }


  // Allocating size for the Total struct, "parse"
  Total * parse = malloc( sizeof(Total) *  (long unsigned int)(pipeCounter + 1) );
  if(pipeCounter > 1) {

        for(i = 0; i < pipeCounter; i++) {
      
        j = 0;

          while(strcmp(t.parseStorage[increment], "|") != 0 
              && strcmp(t.parseStorage[increment], ">") != 0
              && strcmp(t.parseStorage[increment], "<") != 0 
              && strcmp(t.parseStorage[increment], ">>") != 0) {

              parse[i].argument[j] = t.parseStorage[increment]; 
              j++;
              increment++;

            if(increment == t.count) {
              break;
            }
          }

          if(increment == t.count) {  // break out of the forloop
            break;
          }

          if(strcmp(t.parseStorage[increment], ">") == 0) {
            parse[i].directionToken = 2;
            increment++;
          }
          else if(strcmp(t.parseStorage[increment], ">>") == 0) {
            parse[i].directionToken = 3;
            increment++;
          }
          else if(strcmp(t.parseStorage[increment], "|") == 0) {
            parse[i].directionToken = 1;
            increment++;
          }
          else if(strcmp(t.parseStorage[increment], "<") == 0) {
            parse[i].directionToken = 4;
            increment++;
          }
          else {  } 
        }
    } // if pipecounter > 1  

    return parse;

}
*/