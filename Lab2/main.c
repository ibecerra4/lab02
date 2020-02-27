#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>

char *commands[] = { "cd", "help", "exit"};

int main(int argc, char **arg){
	char *line;
	char *command;
	char *input;
	int size = 1024;
	char **history = malloc(sizeof(char)*size);
	
	while(1){
		input = readline("$ ");
		
	}	
}
