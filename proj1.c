#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main() {

  char cwd[1024];
  char host[1024];
  char userName[1024];
  char prompt[4000]; 

    
    
    /* Get the Current Working Directory */
    getcwd(cwd, sizeof(cwd));
    
    /* Get the hostname */
    gethostname(host, sizeof(host));
    
    /* Get the userName */
    strcpy(userName, getlogin());
    
    /* Concatenate the userName, host and working directory */
    strcat(prompt, userName);
    strcat(prompt, "@");
    strcat(prompt, host);
    strcat(prompt, ":");
    strcat(prompt, cwd);
    strcat(prompt, " $");
    fprintf(stdout, "%s\n", prompt);
        

    
    
    return 0;

}

