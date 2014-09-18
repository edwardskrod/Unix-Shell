/**
* shell
* Description:  Main loop which displays the prompt, handles user input and 
* user commands.  printPrompt() displays the prompt while exitShell() 
* is called at exit.  
*/

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include "posixVars.h"
#include "handleInput.h"
#include "handleCommand.h"
#include "commandList.h"

/*  Function Declarations  */
void printPrompt( void );
void exitShell( void );
int main() {

  atexit( exitShell );
  


  status = CONTINUE;
  getcwd(cwd, PATH_MAX);

  while (  status == CONTINUE  ) {
  
  TokenList * tList;
  CommandList * newCommandList = theCommandList();

    printPrompt();

    
    tList = storeInput();
    parseCommandList( newCommandList, tList );
   


   // Free Token List memory
   int i;
   for (i = 0; i < MAX_TOKENS; ++i ) {
       free(tList->parseStorage[i]);
   }
  
   free(tList->parseStorage);
   free(tList);
   tList = NULL;  
   
   CommandList * head = newCommandList;
   Program * p;
   while(newCommandList->program != NULL) {
         handleCommand(newCommandList->program);
         newCommandList->program = newCommandList->program->next; 
  }


     // Free the Program Memory
   while(head->program != NULL) {
       p = head->program;
       for(i = 0; i < 51; i++) {
	       free(p->argv[i]);
	     }
       free(p);
       head->program = head->program->next;
     }

     free(head);

     fflush(stdout);
  }



  if ( status != ERROR )
    return EXIT_SUCCESS;
  else
    return EXIT_FAILURE;

  
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

void exitShell( ) {

  printf ("\nExiting shell.\n" );
  killZombieProcesses( );

}
