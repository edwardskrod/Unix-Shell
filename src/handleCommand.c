#include "handleCommand.h"


void handleCommand(TokenList *tList){

    if (tList->count == 0) {
      	// no command, so just return
    	return;
    } 
    else if (strcmp(tList->parseStorage[0], "exit") == 0) {

    	if (strcmp(tList->parseStorage[1], "") != 0) {

	        int exit_value = atoi(tList->parseStorage[1]);
	        exit(exit_value);
	    }
        else {

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

        if (tList->parseStorage[0][0] == '/') {
            pid_t child;
            int rtn;

            child = fork();

            if (child == 0) {

            rtn = execv(tList->parseStorage[0], (char**)NULL);

            } else {
            
                pid_t child_finished;

                // If the last char is &
                /* child_finished = waitpid(-1, (int *)NULL, WNOHANG); */

                // else, run program in foreground and block parent
                child_finished = waitpid(-1, (int *)NULL, 0);
            }
        }


    }

}