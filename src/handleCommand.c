/**
 * handleCommand
 * Description: Main resource for executing built-ins and 
 * executable system binaries such as "ls" or "grep."
 * Receives the user's input in the form of a list of tokens. 
 * Executes the commands.
 */

#include "handleCommand.h"
#include "tokenize.h"   // SIZE = 100

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

        if ((strcmp(tList->parseStorage[1], "~") == 0) ||
    		(strcmp(tList->parseStorage[1], "~/") == 0) ||
			(tList->parseStorage[1] == NULL) ||
			(strcmp(tList->parseStorage[1], "") == 0) ) {

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
    }
    else if ( strcmp(tList->parseStorage[0], "ioacct") == 0 ) {

        printf("You can suck my balls for entering ioacct, bitch.");








    }

    else {  // executables


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
            //printf("\nNo & in argument.\n");
            isBackgroundProgram = 0;
        }
        else { 
            printf("\nArgument: %s\n", newProgram->argv[newProgram->argc]);
            isBackgroundProgram = 1;

            // Get rid of the &

            char * ptr;
            ptr = strchr(newProgram->argv[newProgram->argc], '&');
            char * newString = strstr(newProgram->argv[newProgram->argc], ptr);
            strncpy(newString, "", sizeof(newString));
            puts(newProgram->argv[newProgram->argc]);

            printf("\nArugment: %s\n", newProgram->argv[newProgram->argc]);

            if (strcmp(newProgram->argv[newProgram->argc], "") == 0) {
                newProgram->argv[newProgram->argc] = NULL;
            }

        }


          //if (tList->parseStorage[0][0] == '/') {
          if (newProgram->name[0] == '/') {  

            pid_t child;
            int rtn;

            child = fork();

            if (child == 0) {

            rtn = execv(newProgram->name, newProgram->argv);

            if ( rtn != 0 ) {

                printf("\nError executing the program. %s", newProgram->name);
            }

            } else {
            
                printf("\nExecuting the program: %s", newProgram->name);

                pid_t child_finished;

              
               if (isBackgroundProgram) {
                    child_finished = waitpid(-1, (int *)NULL, WNOHANG);
               } else {
                    // else, run program in foreground and block parent
                    child_finished = waitpid(-1, (int *)NULL, 0);
                }
            }
        }  else  {
            
            // Get the path of the executable
            char * finalPath = malloc( sizeof(char * ) * 10 );;
            int j = 0;
                
                for(j = 0; j < 15; ++j) {
                    char * currentPath = malloc( sizeof(char * ) * 10 );
                    sprintf(currentPath, "%s/%s",parsedPath[j], tList->parseStorage[0]);
                    
                    if(access(currentPath, F_OK) == 0) {
                        strcpy(finalPath, currentPath);
                        free(currentPath);
                        break;
                    }
                    
                    free(currentPath);
                }



            pid_t child = fork();
            if (child == 0 ) {
            
                int rtn = execv(finalPath, newProgram->argv);
                if ( rtn != 0 ) {

                    printf("\nError executing the program. %s", newProgram->name);
                }
            } else {

                pid_t child_finished;
             
             if (isBackgroundProgram) {
                    
                    child_finished = waitpid(-1, (int *)NULL, WNOHANG);
               } else {

                    // else, run program in foreground and block parent
                    child_finished = waitpid(-1, (int *)NULL, 0);
                }
            }

            // Free all SIZE parsedPath arrays
            int k;
            for (k = 0; k < SIZE; ++k ){

                free(parsedPath[k]);
            } 
            free(parsedPath);
            free(finalPath);

        }

        free(newProgram);


    }


}

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