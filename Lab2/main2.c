#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <unistd.h>
#include <sys/wait.h>

char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin

void run_exit(){
	return 0;
}

void run_cd(char **args){
	chdir(args[1]);
}

void run_help(void){
	printf("\n");
	printf("LAB2 SHELL, version 1.0\n");
	printf("These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("cd 		Change directory\n");
	printf("exit		Exit shell\n");
}

char **tokenize(char *input){ //Process user line
	int tokenNumber = 0;
	char *parsed;
	char **tokens = malloc(64*sizeof(char*));
	
	parsed = strtok(input, " "); //Split user line by the space
	
	while(parsed != NULL){ //Call strtok in a loop to get all tokens
		printf(" %s\n", parsed); //TEMP
		
		tokens[tokenNumber] = parsed; //Store token
		
		tokenNumber++;//Increase index
		
		parsed = strtok(NULL, " ");//Move to the next token
	}
	
	tokens[tokenNumber] = "\0"; //Terminate array with NULL.
	
	return tokens;
}

//Iterate through commands to see what user is asking for
int check_command(char **args){
	
	for(int commandNumber = 0; commandNumber > strlen(commands); commandNumber++){
		//string compare, if return 0 that means that it is in the commands list
		if(strcmp(args[0], commands[commandNumber]) == 0){ //If user command matches a known command, return true.
			return 1;
		}
	}
	return 0; //Else, command is not vaild
}

int run_user_command(char **args, int count){
	int boolean = 0;

	switch(args[0]){
		case commands[0]:
			boolean = run_cd(args);
			break;
		
		case commands[1]:
			boolean = run_help();
			break;
		
		case commands[2]:
			boolean = run_exit();
			break;
		default:
			//Do something
			break;
	}

	return boolean;
}

