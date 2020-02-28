#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>


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
	char *word;
	char **tokens = malloc(64*sizeof(char*));
	
	word = strtok(input, " "); //Split user line by the space
	
	while(word != NULL){ //Call strtok in a loop to get all tokens
		printf(" %s\n", word); //TEMP
		
		tokens[tokenNumber] = word; //Store token
		
		tokenNumber++;//Increase index
		
		word = strtok(NULL, " ");//Move to the next token
	}
	
	tokens[tokenNumber] = '\0'; //Terminate array with NULL.
	
	return tokens;
}

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

//reads user input
int read_line(void){
	char c = getchar();//immediately get first character or user input
	printf("this is C: %c", c);
	int i = 0;//c is character, i is to iterate
	int buffsize = 512;//maximum size of string
	char *line = malloc(sizeof(char)*buffsize);//allocate memory for the user input
	
	printf("outside while loop");
	while(c != '\n'){//while the character is not -1
		printf("inside while loop %i", i);
		line[i]=c;//copy c to line at i
		i++;//increment i to iterate through
		c = getchar();//get character(because we are testing with EOF)
	}
	
	line[i] = '\0';
	
	return line;//return complete user input
}
		

int main(int argc, char **arg){ 
	char *input;
	

	char **command;
	
	while(1){ //While true, runs forever
		printf("$ ");//print command prompt
		input = readline("$ "); //read input from user
		printf("We readeded the line yeiiiii");
		
		command = tokenize(input); //Tokenize the input string to use for arguments later
		printf("we have tokenized  ----------------");
		if(command[0] != NULL){ //While there is a next word in user input,
			int command_number = check_command(command[0]);
			if(command_number != -1){
				run_user_command(command_number, command);
			}
		}
		else{
			printf("error?");
		}
	}
}  
