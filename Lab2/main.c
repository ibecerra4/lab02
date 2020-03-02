#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/types.h>

<<<<<<< HEAD
int flag, pipeAt, countWords;
=======
int flag, pipeAt, redirectFlag;
>>>>>>> 5f8e25441133f529451d05276e93b71428f73756
char *commands[] = { "cd", "help", "exit"}; //Commands to be searched in bin


//method to change directory
void run_cd(char **args){
    chdir(args[1]);
}

//method to print out internally defined commands
void run_help(void){
	printf("\n");
	printf("LAB2 SHELL, version 1.0\n");
	printf("These shell commands are defined internally.  Type 'help' to see this list.\n");
	printf("cd 		Change directory\n");
	printf("exit		Exit shell\n");
	printf("\n");
}

int checkForIORedirection(char** commands){ //Takes tokinzed commands ; Returns 0 for none, 1 for input redirection, 2 for output redirection, -1 for error.
    int redirectInput = 0; //Flags to know what we are redirecting; '<' for input redirection.
    int redirectOutput = 0; //'>' for output redirection.
    int commandNumber = 0; //Index to iterate through commands.

    while(commands[commandNumber] != NULL){ //Check if user input contains '<' or '>' to check for io redirect.
        if(strcmp(commands[commandNumber], ">") == 0){
            redirectInput++; //We need to redirect input.
        }
        if(strcmp(commands[commandNumber], "<") == 0){
            redirectOutput++; //We need to redirect output.
        }
		commandNumber++;
    }

    if(redirectInput > 1 || redirectOutput > 1){ //If we have multiple redirections, then we have an error.
        return -1;
    }
    else if(redirectInput = 1 && redirectOutput == 0){//Then we redirect input
        return 1;
    }
    else if(redirectOutput = 1 && redirectInput == 0){//Then we redirect output
        return 2;
    }
    else{ //Else, there is no IO redirection.
        return 0;
    }
}


char* getFileName(char** commands){//Get the argument before the "<" or ">" symbol.
    int commandNumber = 0;
	while(commands[commandNumber] != NULL){
        if(strcmp(commands[commandNumber], "<") == 0 || strcmp(commands[commandNumber], ">") == 0){
            return commands[commandNumber - 1];
        }
		commandNumber++;
    }
    return NULL;
}
//Method based of http://people.cs.pitt.edu/~khalifa/cs449/spr07/Assigns/Assign4/myshell.c do_command method.
int redirect(char **commands, int IOflag, char* fileName) { //Takes processed user input, the flag that contains the opertaion to perform, and the file name.
  
  int result;
  pid_t child_id;
  int status;

  // Fork the child process
  child_id = fork();

  if(child_id == 0) {
    // Set up redirection in the child process
    if(IOflag == 1){
      freopen(fileName, "r", stdin);
    }
    else if(IOflag == 2){
      freopen(fileName, "w+", stdout);
    }
    // Execute the command
    result = execvp(commands[0], commands);

    exit(-1);
    }
}

char **tokenize(char *input){ //Process user line
	int tokenNumber = 0;
	char *word;
	char **tokens = malloc(64*sizeof(char*));
	
	word = strtok(input, " /"); //Split user line by the space
	
	while(word != NULL){ //Call strtok in a loop to get all tokens

		tokens[tokenNumber] = word; //Store token
		
		//if found pipe, then set flag to 1 so when calling from main, execute pipe command if flag is 1
		if(strcmp(tokens[tokenNumber], "|")== 0){
			flag = 1;
			pipeAt = tokenNumber; 
		}

		tokenNumber++;//Increase index
		
		word = strtok(NULL, " /");//Move to the next token
	}
	
	tokens[tokenNumber] = '\0'; //Terminate array with NULL.
	
	if(checkForIORedirection(tokens)){
		redirectFlag = 1;
	}

	return tokens;
}

char **before_split_tokenizer(char **args){
	char **before_pipe;
	int i =0;
	while( i != pipeAt){
		before_pipe[i] = args[i];
		i++;
	}
	return before_pipe;
}

char **after_split_tokenizer(char **args){
	char **after_pipe;
	int i=pipeAt;
	while(i != countWords){
		after_pipe[i] = args[i];
		i++;
	}
	return after_pipe;	
}

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
	printf("%s@%s%s", getenv("USER"), cwd, getenv("PS1"));//print USER, HOME, and PS1
} 

//method to run a command that pipes
void run_piped_command(char **args1, char **args2){
	int my_pipe[2];//pipe[0] reads, pipe[1] writes
	pid_t p1, p2;
	
	pipe(my_pipe);
	
	p1 = fork();
	if(p1<0){//fork failed
		printf("fork failed\n"); 
		exit(1);
	}
	if(p1 == 0){//child 1 executes
		close(my_pipe[0]); //close reading entrance because we only want to write
		dup2(my_pipe[1], 1);
		close(my_pipe[0]);//close reading entrance
		if(execvp(args1[0], args1) < 0){
			printf("%s: command not found", args1[0]);//if execvp returns -1, print command
			exit(0);
		}
	}else{//child 2 executes
		p2 = fork();
		
		if(p2<0){
			printf("Fork failed\n"); 
			exit(1);
		}
		if (p2 == 0){
			close(my_pipe[1]);//close writing entrance because we only want to read 
			dup2(my_pipe[0], 0);
			close(my_pipe[1]); //close writing entrance
			if(execvp(args2[0], args2) < 0){
				printf("%s: command not found", args2[0]);//if execvp returns -1, print command
				exit(0);
			}
		} else{
			wait(NULL);
			wait(NULL);
		}			
	}
}

//method to run a normal command without pipes
void run_normal_command(char **command){
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
			}
			else{//if command doesn't exist in built in, then use execvp to use bin commands
				if(flag != 1){//run normal command if no pipe found during tokenizing
					run_normal_command(command);
				}
				else{//run command if pipe is found during tokenizing
					char ** before_pipe = before_split_tokenizer(command);
					char ** after_pipe = after_split_tokenizer(command);
				
					run_piped_command(before_pipe, after_pipe);
<<<<<<< HEAD
				}printf("inside else");
=======
				}
				if(redirectFlag == 1){
					int operation = checkForIORedirection(command);
					redirect(command, operation, getFileName(command));
				}
>>>>>>> 5f8e25441133f529451d05276e93b71428f73756
			}
		}
		free(input);//free token
		free(command);//free tokenizer
	}
}
