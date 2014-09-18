#include <string.h>
#include "commandList.h"
#include "program.h"
/**
* commandList
* Description:  parseCommandList takes a TokenList and parses it into programs
*
*/
CommandList * theCommandList()
{
  CommandList * commandList = (CommandList *)malloc(sizeof(CommandList));
  commandList->program = NULL;
  commandList->numberOfPrograms = 0;
  return commandList;
}
void parseCommandList( CommandList * newCommandList,  TokenList * tList   ) {

Program *currentProgram = theProgram();
newCommandList->program = currentProgram;
newCommandList->numberOfPrograms = 0;


	// Parse the List of Tokens into Programs
	int lcv = 0;
	while (    tList->parseStorage[lcv] != NULL    ){
	  char * token = tList->parseStorage[ lcv ];
	      if(strcmp(token, "|")== 0)
		{
		  currentProgram->redirect = PIPE;
		  currentProgram->next = theProgram();
		  currentProgram->next->redirect = PIPE;
		  currentProgram = currentProgram->next;
		  ++lcv;
		}
	      else if(strcmp(token, ">>") == 0)
		{
		  currentProgram->redirect = APPEND;
		  currentProgram->next = theProgram();
		  currentProgram->next->redirect = APPEND;
		  currentProgram = currentProgram->next;
		  ++lcv;
		}
	      else if (strcmp(token, ">") == 0)
		{
		  currentProgram->redirect = OUT;
		  currentProgram->next = theProgram();
		  currentProgram->next->redirect = OUT;
		  currentProgram = currentProgram->next;
		  ++lcv;
		}
	      else if (strcmp(token, "<") == 0)
		{
		  currentProgram->redirect = IN;
		  currentProgram->next = theProgram();
		  currentProgram->next->redirect = IN;
		  currentProgram = currentProgram->next;
		  ++lcv;
		}
	      else
		{
		  int counter = 0;
		  newCommandList->numberOfPrograms++;
		  while(tList->parseStorage[lcv] != NULL &&
			strcmp(tList->parseStorage[lcv], "|") != 0 &&
			strcmp(tList->parseStorage[lcv], ">>") != 0 &&
			strcmp(tList->parseStorage[lcv], ">") != 0 &&
			strcmp(tList->parseStorage[lcv], "<") != 0)
			
		    {
		      strcpy(currentProgram->argv[counter], tList->parseStorage[lcv]);
		      currentProgram->argc++;
		      //printf("\ncurrentProgram[%d] = %s\n", counter, currentProgram->argv[counter]);
		      lcv++;
		      counter++;
		    }
		  currentProgram->name = currentProgram->argv[0];
		  currentProgram->argv[counter] = NULL;
		}
	}	// End while (  lcv < tList->count  )
}
