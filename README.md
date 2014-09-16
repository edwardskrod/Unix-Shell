#deviation fromnominal requirements
# Known errors and / or missing features
# description of any bonus implemented


# Project 1:  Implementing a Shell

# Developers:  Edward Skrod, Sean Adams

# Date:  September 17, 2014

# Summary
	Unix shell that takes user input and executes a subset of 
	a typical shell's commands.  The code supports built-ins cd, exit and ioacct.  It also supports forking, i/o redirects, pipes, and
	background processing.

# Compilation
1. cd src
2. make (or "make -s" to quiet the make process)

# How to Run the Shell
1. ./shell

# Exiting the Shell
1. exit

# Division of Responsibilities

1. To do



# Files
1. makefile
	Compiles the program
	
2. shell.c
	Main loop which displays the prompt, handles user input and 
	user commands.  printPrompt() displays the prompt while exitShell() 
	is called at exit.  

3. handleInput.h, handleInput.c
	Stores the user's input into an array of C strings which we call "tokens."  Tracks the number of tokens.

4. handleCommand.h, handleCommand.c
	Main resource for executing built-ins and executable system binaries such as "ls" or "grep."
	Receives the user's input in the form of a list of tokens.  Executes the commands.  Also performs the ioacct command which gets the total bytes read and written by a process.

5. posixVars.h
	Many Linux systems define the sizes for host name, path name, etc. in a file called posix1_lim.h.   If at all possible, we wanted to use these sizes in our shell.  However, in the case that these sizes are not defined, we needed to define them ourselves in the posixVars.h header file.  We also defined a few global variables, such as the current working directory and previous working directory here as well.

6. tokenize.h, tokenize.c
	Receives the $PATH environment variable and tokenizes it based upon the ":" delimiter into an array of C strings.  We check this array for the location of an executable in handleCommand.c

7. program.h, program.c
	Defines a program and instantiates it witl default values upon creation.  Used by handleCommand.c when the user input is not a built-in but rather an executable.

8. executeCommand.h, executeCommand.c
	Execute command executes the binary.  If the binary is not a 
	direct path, it calls getFinalPath() to determine where the binary resides.

