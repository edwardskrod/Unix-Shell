/**
 * handleCommand
 * Description: Main resource for executing built-ins and 
 * executable system binaries such as "ls" or "grep."
 * Receives the user's input in the form of a list of tokens. 
 * Executes the commands.
 */

#include "handleCommand.h"
#include "tokenize.h"   

void handleCommand(TokenList *tList){
  

    if (tList->count == 0) {
      	// no command, so just return
    	return;
    } 
    else if (strcmp(tList->parseStorage[0], "exit") == 0) {

    	if ((tList->parseStorage[1] != NULL) && (strcmp(tList->parseStorage[1], "") != 0)) {

	        int exit_value = atoi(tList->parseStorage[1]);
            status = EXIT;
	        exit(exit_value);
	    }
        else {

            status = EXIT;
	    	exit(EXIT_SUCCESS);
	    }
    }
    else if ( strcmp(tList->parseStorage[0], "cd") == 0 ) {   	

        int returnVal = 0;

        if (  (tList->parseStorage[1] == NULL) ||
              (strcmp(tList->parseStorage[1], "~") == 0) ||
    		  (strcmp(tList->parseStorage[1], "~/") == 0) ||
			  (strcmp(tList->parseStorage[1], "") == 0)) {

                strncpy(pwd, cwd, sizeof(pwd));
				chdir(getenv("HOME"));
                getcwd(cwd, PATH_MAX);
		}
		else if (strcmp(tList->parseStorage[1], "-") == 0){

            returnVal = chdir(pwd);
			strncpy(pwd, cwd, sizeof(pwd));
            getcwd(cwd, PATH_MAX);
        }

        else if (strcmp(tList->parseStorage[1], ".") == 0) {
            
            // Set the previous working directory to the current working dir
            getcwd(pwd, PATH_MAX);
        }

        else if ( strcmp(tList->parseStorage[1], "..") == 0)  {

            strncpy(pwd, cwd, sizeof(pwd));
            char * ptr;
            ptr = strrchr(cwd, '/');
            char * newString = strstr(cwd, ptr);
            strncpy(newString, "", sizeof(newString));
            puts(cwd);
            returnVal = chdir(cwd);
            getcwd(cwd, PATH_MAX);

        }
        else {
            returnVal = chdir(tList->parseStorage[1]);
        }
        
        if (returnVal == -1) {
            printf("Error: No such file or directory.\n");
        }
    } else {  // executables

        int isIoacct = 0;

        if ( strcmp(tList->parseStorage[0], "ioacct") == 0 ) {

            int lcv = 1;
            while (tList->parseStorage[lcv] != NULL) {

                strcpy(tList->parseStorage[lcv - 1], tList->parseStorage[ lcv ]);
                ++lcv;
            }
            tList->parseStorage[lcv -1 ] = NULL;

            // set Flag
            isIoacct = 1;

        }
           
    
        Program * newProgram = theProgram();
        char ** parsedPath = pathParser();
        int isBackgroundProgram;            // 1 if BG, 0 if not

        // populate newProgram->name with the first arg
        newProgram->name = tList->parseStorage[0];

        // The first arg, by convention, is the name of the executable
        newProgram->argv[0] = tList->parseStorage[0];

        // Get args - start at position 1
        int lcv = 1; // loop control variable
        while ((tList->parseStorage[lcv] != NULL) && (strcmp(tList->parseStorage[lcv], "") != 0 )) {
            newProgram->argv[lcv] = tList->parseStorage[lcv];
            ++newProgram->argc;
            ++lcv;

        }

        // add a null 
        newProgram->argv[newProgram->argc + 1] = NULL;

        /*  Check for the &  */
        if ( strrchr(newProgram->argv[newProgram->argc], '&')  == NULL  ){
            isBackgroundProgram = 0;
        }
        else { 

            isBackgroundProgram = 1;
            char * ptr;
            ptr = strchr(newProgram->argv[newProgram->argc], '&');
            char * newString = strstr(newProgram->argv[newProgram->argc], ptr);
            strncpy(newString, "", sizeof(newString));
            puts(newProgram->argv[newProgram->argc]);

            if (strcmp(newProgram->argv[newProgram->argc], "") == 0) {
                newProgram->argv[newProgram->argc] = NULL;
            }

        }
  
        /*  EXECUTE THE COMMAND  */
        executeCommand( tList, newProgram, isIoacct, parsedPath, isBackgroundProgram );
         

        /*  FREE ALL THA MEMORIES   */
        int k;
        for (k = 0; k < SIZE; ++k ){
            free(parsedPath[k]);
        } 
        free(parsedPath);
        free(newProgram);

    } // end executables
}  // End handleCommand.c

/**
 * Kill Zombie Processes
 * Description: Kills processes that have not yet been handled by
 *              their parent process. 
 */
void killZombieProcesses() {

    pid_t pid;

    // Kill processes as long as we keep finding them
    while ( ( pid = waitpid( -1, 0, WNOHANG ) )  )
        
        // No zombie processes are found
        if ( pid == -1 || pid == 0 )
            break;

}