#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

/*---------------POSIX VARIABLES -----------------------*/
/* http://linux.die.net/man/3/sysconf                   */
/* The following _POSIX define statements are included in 
LINUX builds from the posix1_lim.h file.  To make the code
useable on OSX builds, we have created define statements.

LINUX defines _POSIX_HOST_NAME_MAX as 255.  
The following code allows us to use the const on MacOSX.  */
#ifndef HOST_NAME_MAX
  #ifdef _POSIX_HOST_NAME_MAX
    #define HOST_NAME_MAX _POSIX_HOST_NAME_MAX
  #else 
    #define HOST_NAME_MAX 255
  #endif
#endif

/* LINUX defines _POSIX_LOGIN_NAME_MAX as 9.  The 
following code allows us to use the const on MacOSX.  */
#ifndef LOGIN_NAME_MAX
  #ifdef _POSIX_LOGIN_NAME_MAX
    #define LOGIN_NAME_MAX _POSIX_LOGIN_NAME_MAX
  #else
    #define LOGIN_NAME_MAX 9
  #endif
#endif

/* LINUX defines _POSIX_LOGIN_NAME_MAX as 255.  The 
following code allows   us to use the const on MacOSX.  */
#ifndef PATH_MAX
  #ifdef _POSIX_PATH_MAX
    #define PATH_MAX _POSIX_PATH_MAX
  #else
    #define PATH_MAX 255
  #endif
#endif

void printPrompt(  );
int main() {



  printPrompt();


  return 0;
}

void printPrompt( )
/* Builds a string from the Current Working Directory, 
hostName and loginName and prints it to the console in the 
format <username>@<hostname>:<working_directory> $
 */
{
  char cwd[ PATH_MAX + 1 ];
  char hostName[ HOST_NAME_MAX + 1 ];
  char loginName[ LOGIN_NAME_MAX + 1 ];

  /* Get the Current Working Directory */
  getcwd( cwd, PATH_MAX );
  
  /* Get the hostname */
  gethostname( hostName, HOST_NAME_MAX );
  
  /* Get the loginName */
  getlogin_r( loginName, LOGIN_NAME_MAX );

  /* Make sure the strings are null terminated */
  cwd[PATH_MAX] = 0;
  hostName[ HOST_NAME_MAX ] = 0;
  loginName[ LOGIN_NAME_MAX ] = 0;

  fprintf( stdout, "%s@%s:%s $ \n", loginName, hostName, cwd );

  // flush stdout
  fflush( stdout );

}
