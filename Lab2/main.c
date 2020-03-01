#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>

int flag, pipeAt;
char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin

//method to change directory
void run_cd(char **args){
	chdir(args[1]);
}

//method to print out internally defined commands
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
	
	word = strtok(input, " /"); //Split user line by the space
	
	while(word != NULL){ //Call strtok in a loop to get all tokens

		tokens[tokenNumber] = word; //Store token
		
		//if found pipe, then set flag to 1 so when calling from main, execute pipe command
		if(strcmp(tokens[tokenNumber], "|")== 0){
			flag = 1;
			pipeAt = tokenNumber;
		}

		tokenNumber++;//Increase index
		
		word = strtok(NULL, " /");//Move to the next token
	}
	
	tokens[tokenNumber] = '\0'; //Terminate array with NULL.
	
	return tokens;
}

char **pipe_tokenizer(char **tokens){
	int tokenNumber =0;
	char *word;
	char **tokens_before_pipe =tokens;
	char **tokens_after_pipe = malloc(64*sizeof(char*));	
	
	while(
	

//Iterate through commands to see what user is asking for
int check_command(char **args){
	//iterate through command lists to search if the command is from our built in list
	for(int commandNumber = 0; commandNumber < 3; commandNumber++){
		//string compare, if return 0 that means that it is in the commands list
		if(strcmp(args[0], commands[commandNumber]) == 0){ //If user command matches defined command, return true.
			return commandNumber;//return index number so that we can use it with run_user_command
		}
	}
	return -1; //Else, command is not from our built in commands
}

//method accepts index of the command needing to execute and the arguments
void run_user_command(int commandNumber, char **args){ //  
	switch(commandNumber){
		case 0://if index 0, run the cd method
		    run_cd(args);
			break;
		
		case 1://if index 1, run the help method
			run_help();
			break;
		
		case 2://if index 2, exit the shell
            		exit(0);
            
		default:
			//Do something
			break;
	}
}


//method to print the current working directory
void pwd(){
	char cwd[1024]; 
	getcwd(cwd, sizeof(cwd));//get current working directory
	setenv("PS1", "$", 1);//override PS1 variable with dollar sign
	printf("%s@%s%s", getenv("USER"), getenv("HOME"), getenv("PS1"));//print USER, HOME, and PS1
	printf(":%s", cwd); //print working directory
} 

//method to run a command that pipes
void run_pipe_command(char **args1, char args2){
	int my_pipe[2];//pipe[0] reads, pipe[1] writes
	pid_t p1, p2;
	
	pipe(my_pipe);
	
	p1 = fork();
	if(p1<0){//fork failed
		printf("fork failed\n"); 
		exit(1);
	}
	if(p1 == 0){//child 1 executes
		close(my_pipe[1]);

	}else{//child 2 executes
		p2 = fork();
		
		if(p2<0){
			printf("fork failed\n"); 
			exit(1);
		}
		if (p2 == 0){
			close(my_pipe[1]);//close write side because we only want to read 
			read(my_pipe[0], ,);
			close(my_pipe[0]); //close reading entrance
			if(execvp(,) < 0){
				printf("");
				exit(0);
			}
		}			
	}
}

int main(int argc, char **arg){ 
	char *input;//user input
	char **command;//pointer of pointers for commands

	while(1){ //While true, runs forever
		printf("\n");
		pwd();//print working directory

		input = readline(""); //read input from user
		
		command = tokenize(input); //Tokenize the input string to use for arguments later

		if(command[0] != NULL){ //While there is a next word in user input,			
			int command_number = check_command(command);//check if command exists
			if(command_number != -1){//if command does exist, then run the command
				run_user_command(command_number, command);//running the command
			}else{//if command doesn't exist in built in, then look through bin
				//Forking process to get parent and child
				int p = fork();
				if(p<0){//fork failed, exit
					printf("fork failed\n");
					exit(1);
				}
				else if(p==0){//child process
					if(execvp(command[0], command) < 0){ //look through bin and execute
						printf("%s: command not found", command[0]);//if execvp returns -1, print command not found
						exit(1);
					}
				} else{//parent proccess
					wait(NULL);//make the parent wait
				}
			}
		}
		free(input);//free token
		free(command);//free tokenizer
	}
}  
