// import requried libraries
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include<sys/wait.h>

/*
Program is a small OS shell that takes user input command. If input is built in, program
executes request else, program forks a new process and excutes command with execve
if command exists. 
Author: JASON YANG 10/26/2020
*/
#define MAX_LEN 20
int main(){
  while(1){
    printf("lab1>");
    // init input string
    char input[MAX_LEN];
    // scan for user input
    scanf("%s",input);
    // convert input to lowercase
    int i;
    for(i = 0; input[i]; i++){
      input[i] = tolower(input[i]);
    }
    // print parent PID
    printf("Parent process %d\n", getpid());
    // case when user enters "greet"
    if (strcmp(input,"greet")==0){
      printf("Hello\n");
    }
    // case when user enters "printid"
    else if (strcmp(input,"printid")==0){
      printf("%d\n", getpid());
    }
    // case when user enters "exit"
    else if (strcmp(input,"exit")==0){
      exit(0);
    }
    // case when input is not built in command
    else{
      // create child process
      pid_t pid;
      pid = fork();
      // error handling for fork failure
      if (pid<0){
        fprintf(stderr, "Fork Failed");
        exit(-1);
      }
      // child process
      else if (pid==0){
        printf("Child process %d will execute the command %s\n", getpid(), input);
        // concatenate path for execve
        char path[128] = "/bin/";
        strcat(path,input);
        char *param[]={path, NULL};
        // child process into new process -> executes user input if valid
        execve(path, param, NULL);
        // execve failed -> print and exit
        printf("Command Not Found!\n");
        exit(0);
      }
    }
    // wait for child processes to finish
    wait(NULL);
  }
}
