Created by Ivanna Becerra and Andres Silva.
Shell for Operating Systems | Dr. Roach | Feb 28th, 2020

The following program is a simple shell that has build in commands 
such as cd (change directory), help (print a brief description of
available commands) and exit (exit the shell).

The shell works by accepting an input line from the user, tokenizing it,
checking that the user provided command exists (else print an error message),
and if the command is valid, then execute by calling the appropiate method.

The shell with prompt the user with "$" and print the working directory
by using "cdw" and "getenv" of PS1 and HOME (since HOST is not an enviroment 
variable).

For commands that are not buid in, the program will fork and look for the
desired command inside bin using execvp, where it might be found and then 
ran.


