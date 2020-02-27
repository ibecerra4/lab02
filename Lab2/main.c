#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin

int main(int argc, char **arg){ 
	char *input;
	char **command;
	int buffsize = 1024;
	char **history = malloc(sizeof(char)*buffsize); //History to hold previous and next user input 

	while(1){ //While true,
		input = readline("$ "); //Prompt with "$" for input
		command = tokenize(input); //Proccess input word by word

		if(command[0] != NULL){ //While there is a next word in user input,
				
		}
		else{
			
		}
	}
}

void run_command(char **args){
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
	
	/*** Maybe change loop to a "do while" ***/
	
	parsed = strtok(input, " "); //Split user line by the space
	
	while((token != NULL){ //Call strtok in a loop to get all tokens
		printf(" %s\n", token); //TEMP
		
		tokens[tokenNumber] = parsed; //Store token
		
		tokenNumber++;//Increase index
		
		parsed = strtok(NULL, " ");//Move to the next token
	}
	
	tokens[tokenNumber] = NULL; //Terminate array with NULL.
	
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
