#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>


char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin

void run_cd(char **args){
	chdir(args[1]);
}

void run_help(void){
	printf("\n");
	printf("LAB2 SHELL, version 1.0\n");
	printf("These shell commands are defined internally.  Type `help' to see this list.\n");
	printf("cd 		Change directory\n");
	printf("exit		Exit shell\n");
	printf("\n");
}

char **tokenize(char *input){ //Process user line
	int tokenNumber = 0;
	char *word;
	char **tokens = malloc(64*sizeof(char*));
	
	word = strtok(input, " "); //Split user line by the space
	
	while(word != NULL){ //Call strtok in a loop to get all tokens

		tokens[tokenNumber] = word; //Store token
		
		tokenNumber++;//Increase index
		
		word = strtok(NULL, " ");//Move to the next token
	}
	
	tokens[tokenNumber] = '\0'; //Terminate array with NULL.
	
	return tokens;
}

//Iterate through commands to see what user is asking for
int check_command(char **args){
	
	for(int commandNumber = 0; commandNumber < 3; commandNumber++){
		//string compare, if return 0 that means that it is in the commands list
		if(strcmp(args[0], commands[commandNumber]) == 0){ //If user command matches a known command, return true.
			return commandNumber;
		}
	}
	return -1; //Else, command is not vaild
}


void run_user_command(int commandNumber, char **args){ //  
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

void pwd(){
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd)); 
	printf(":%s", cwd); 
} 

int main(int argc, char **arg){ 
	char *input;
	//struct stat file_stat;

	char **command;
	
	while(1){ //While true, runs forever
		pwd();
		input = readline("$ "); //read input from user
		
		command = tokenize(input); //Tokenize the input string to use for arguments later

		if(command[0] != NULL){ //While there is a next word in user input,			
			int command_number = check_command(command);//check if command exists
			if(command_number != -1){//if command does exist, then run the command
				run_user_command(command_number, command);//running the command
			}
		}
		/*else if{//if command doesn't exist in built in, then look through bin
			//int my_pipe[2];//pipe[o] reads, pipe[1] writes
			//pipe(my_pipe);
			//Forking process to get parent and child
			int p = fork();
			if(p<0){
				printf("fork failed\n");
				return;
			}
			e/*lse if(p==0){//child process
				if(stat(command[0], &file_stat) == 0){ //if given absolute path, execute
					execve(command[0], command, getenv("PATH"));
				}
			else{
				
			}printf("\n");
		}
		else{
			printf("command not found");
		}*/
	}
}  
