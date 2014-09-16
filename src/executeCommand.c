#include "executeCommand.h"

/**
*  executeCommand
*  Description:  execute command executes the binary.  If the binary is not a 
* direct path, it calls getFinalPath() to determine where the binary resides.
*
*/
void executeCommand(TokenList * tList, Program * newProgram,  int isIoacct, 
					char ** parsedPath, int isBackgroundProgram){

	/* If direct path */	
	if (newProgram->name[0] == '/') {  

	execute( newProgram->name, newProgram->argv, isIoacct, isBackgroundProgram );

	} else  {
	    
	char * finalPath = getFinalPath( parsedPath, tList );
	execute(finalPath, newProgram->argv, isIoacct, isBackgroundProgram );
   
	free(finalPath);
	
	}
}

/**
* getFinalPath
* Description:   takes the array of paths and find the path
* associated with the process
* Must free the final Path in main function
* Called by executeCommand
*/
char * getFinalPath( char ** parsedPath, TokenList * tList ) {

	char * fPath = malloc( sizeof(char * ) * 10 );;
    int j = 0;
        
     for(j = 0; j < 15; ++j) {
        char * currentPath = malloc( sizeof(char * ) * 10 );
        sprintf(currentPath, "%s/%s",parsedPath[j], tList->parseStorage[0]);
            
        if(access(currentPath, F_OK) == 0) {
            strcpy(fPath, currentPath);
            free(currentPath);
            break;
        }
            
        free(currentPath);
    }

    return fPath;
}


/**
* execute
* Description:  executes the process
*/
void execute( char * name, char ** args, int isIoacct, int isBackgroundProgram  ) {

 		pid_t child;
	    int rtn;

	    child = fork();

	    if (child == 0) {

	        rtn = execv(name, args);

	        if ( rtn != 0 ) {

	         printf("\nError executing the program. %s\n", name);
	        }

	    } else {

	        if ((isIoacct) && (!isBackgroundProgram)){
	           ioacct(child);
	        } else if (isBackgroundProgram) {
	            pid_t child_finished;
	            child_finished = waitpid(-1, (int *)NULL, WNOHANG);

	        } else {
	            // Not a background, not ioacct
	            pid_t child_finished;
	            child_finished = waitpid(-1, (int *)NULL, 0);
	        }
	    }
}

/**
* ioacct
* Description:  receives a child process PID, find the process in /proc/%child%/id
* and gets the total number of bytes read and written.
*
*
*/
void ioacct( pid_t child ) {

    char filename[100];
    char test[100];

    int tempBytes = -1;
    int readBytes = -1;
    int writeBytes = -1;
    pid_t child_finished = -999;            // pid is never going to be this

    sprintf(filename, "/proc/%d/io", (int)child);
    FILE* proc_file = fopen(filename, "r"); // open the proc file for eading

    while ((child != child_finished)) {

        //read from the file
        int count = 0;
        while (fscanf(proc_file, "%s %d", test, &tempBytes) > 0) {
            if (count == 4) {
                readBytes = tempBytes;
            }
            if (count == 5) {
                writeBytes = tempBytes;
            }
            ++count;
        }
        child_finished = waitpid(-1, (int *)NULL, 0);
    }
    printf("\nBytes Read: %d\nBytes Written: %d\n", readBytes, writeBytes);
}



