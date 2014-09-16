#include "command.h"
#include "program.h"
/**
*
*
*
*/
CommandList * parseCommandList( CommandList * newCommandList,  TokenList * tList   ) {


	
    Program *currentProgram = newCommandList->program = theProgram();

  

	// Parse the List of Tokens into Programs
	int lcv = 0;
	while (    tList->parseStorage[lcv] != NULL    ){

		char * token = tList->parseStorage[ lcv ];



			if (  !isRedirection( token ) && !isPipe( token )  ) {
			
			   currentProgram->name = currentProgram->argv[0] = token;
			   new = 0;
			}
			else {
				printf ("Error:  <,>, or | cannot be at the beginning of a command.");
			}
	











		++lcv;

	}	// End while (  lcv < tList->count  )




	// return the CommandList
   	return newCommandList;
}

/**  HELPER FUNCTIONS  **/


/**
 * Checks if token is < or >
 */
bool isRedirection( const char * str ) {
	return ( *str == '<' || *str == '>' );
}

/**
 * Checks if token is |
 */
bool isPipe( const char * str ) {
	return ( strlen(str) == 1 && ( *str == '|' ) );
}