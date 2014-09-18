/**
 * handleCommand
 * Description: Main resource for executing built-ins and 
 * executable system binaries such as "ls" or "grep."
 * Receives the user's input in the form of a list of tokens. 
 * Executes the commands.
 */

#include "handleCommand.h"
#include "tokenize.h"   

void handleCommand(Program * program){
  

    if (program->argc == 0) {
      	// no command, so just return
    	return;
    } 
    else if (strcmp(program->argv[0], "exit") == 0) {
      
    	if ((program->argv[1] != NULL) && (strcmp(program->argv[1], "") != 0)) {

	        int exit_value = atoi(program->argv[1]);
            status = EXIT;
	        exit(exit_value);
	    }
        else {

            status = EXIT;
	    	exit(EXIT_SUCCESS);
	    }
    }
    else if ( strcmp(program->argv[0], "cd") == 0 ) {   	

        int returnVal = 0;
	
        if (  (program->argv[1] == NULL) ||
              (strcmp(program->argv[1], "~") == 0) ||
    		  (strcmp(program->argv[1], "~/") == 0) ||
			  (strcmp(program->argv[1], "") == 0)) {

                strncpy(pwd, cwd, sizeof(pwd));
				chdir(getenv("HOME"));
                getcwd(cwd, PATH_MAX);
		}
		else if (strcmp(program->argv[1], "-") == 0){

            returnVal = chdir(pwd);
			strncpy(pwd, cwd, sizeof(pwd));
            getcwd(cwd, PATH_MAX);
        }

        else if (strcmp(program->argv[1], ".") == 0) {
            
            // Set the previous working directory to the current working dir
            getcwd(pwd, PATH_MAX);
        }

        else if ( strcmp(program->argv[1], "..") == 0)  {

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
            returnVal = chdir(program->argv[1]);
        }
        
        if (returnVal == -1) {
            printf("Error: No such file or directory.\n");
        }
    } else {  // executables

        int isIoacct = 0;

        if ( strcmp(program->argv[0], "ioacct") == 0 ) {

            int lcv = 1;
            while (program->argv[lcv] != NULL) {

                strcpy(program->argv[lcv - 1], program->argv[ lcv ]);
                ++lcv;
            }
            program->argv[ lcv - 1 ] = NULL;

            // set Flag
            isIoacct = 1;

        }
           

	    char ** parsedPath = pathParser();
        int isBackgroundProgram;            // 1 if BG, 0 if not


	
        /*  Check for the &  */
        if ( strrchr(program->argv[program->argc - 1], '&')  == NULL  ){
            isBackgroundProgram = 0;
        }
        else { 
	  
            isBackgroundProgram = 1;
            char * ptr;
            ptr = strchr(program->argv[program->argc - 1], '&');
            char * newString = strstr(program->argv[program->argc - 1], ptr);
            strncpy(newString, "", sizeof(newString));
            puts(program->argv[program->argc - 1]);

            if (strcmp(program->argv[program->argc - 1], "") == 0) {
                program->argv[program->argc - 1] = NULL;
            }

        }
  
        /*  EXECUTE THE COMMAND  */
        executeCommand(  program, isIoacct, parsedPath, isBackgroundProgram  );
         

        /*  FREE ALL THA MEMORIES in PARSED PATH  */
        int k;
        for (k = 0; k < SIZE; ++k ){
            free(parsedPath[k]);
        } 
        free(parsedPath);
        
	//WE COMMENTED THIS OUT
	//free(newProgram);

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
