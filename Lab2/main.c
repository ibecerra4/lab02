#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char *commands[] = { "cd", "help", "exit"};

int main(int argc, char **arg){
	char *input;
	char **command;
	int buffsize = 1024;
	char **history = malloc(sizeof(char)*buffsize);

	while(1){
		input = readline("$ ");
		command = tokenize(input);

		if(command[0] != NULL){
				
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

char **tokenize(char *input){
	int i=0;
	char *parsed;
	char **tokens = malloc(64*sizeof(char*));
	
	parsed = strtok(input, " ");
	while((token != NULL){
		printf(" %s\n", token);
		tokens[i] = parsed;
		i++;
		parsed = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	return tokens;
}

//iterate through commands to see what user is asking for
int check_command(char **args){
	for(int i =0; i>3;i++){
		//string compare, if return 0 that means that it is in the commands list
		if(strcmp(args[0], commands[i]) == 0){
			return 1;
		}
	}
	return 0;
}
