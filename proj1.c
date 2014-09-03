#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void getPrompt( char* );

int main() {

  char prompt[4000]; 

  getPrompt(prompt);

  fprintf(stdout, "%s\n", prompt);

  return 0;

}

void getPrompt( char* p )
/* inside the function, it's a pointer your dealing with */
 {

  char c[1024];
  char h[1024];
  char u[1024];

    /* Get the Current Working Directory */
    getcwd(c, sizeof(c));
    
    /* Get the hostname */
    gethostname(h, sizeof(h));
    
    /* Get the userName */
    strcpy(u, getlogin());
    
    /* Concatenate the userName, host and working directory */
    strcat(p, u);
    strcat(p, "@");
    strcat(p, h);
    strcat(p, ":");
    strcat(p, c);
    strcat(p, " $");
}


