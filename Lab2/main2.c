#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <unistd.h>
#include <sys/wait.h>

char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin

//Iterate through commands to see what user is asking for
int check_command(char **args){
	
	for(int commandNumber = 0; commandNumber > strlen(commands); commandNumber++){
		//string compare, if return 0 that means that it is in the commands list
		if(strcmp(args[0], commands[commandNumber]) == 0){ //If user command matches a known command, return true.
			return commandNumber;
		}
	}
	return -1; //Else, command is not vaild
}

int run_user_command(int commandNumber, char **args){ //  
	switch(commandNumber){
		case 0:
		    run_cd(args);
			break;
		
		case 1:
			run_help();
			break;
		
		case 2:
            exit(0);
            
		default:
			//Do something
			break;
	}
}