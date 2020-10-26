#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include<sys/wait.h>


#define MAX_LEN 50
int main(){
  while(1){
    printf("lab1>");
    char input[MAX_LEN];
    scanf("%s",input);
    for(int i = 0; input[i]; i++){
      input[i] = tolower(input[i]);
    }
    printf("Parent process %d\n", getpid());

    if (strcmp(input,"greet")==0){
      printf("Hello\n");
    }
    else if (strcmp(input,"printid")==0){
      printf("%d\n", getpid());;
    }
    else if (strcmp(input,"exit")==0){
      exit(0);
    }

    else{
      pid_t pid;
      pid = fork();
      if (pid<0){
        fprintf(stderr, "Fork Failed");
        exit(-1);
      }
      else if (pid==0){
        printf("Child process %d will execute the command %s\n", getpid(), input);
        char path[128] = "/bin/";
        strcat(path,input);
        char *param[]={path, NULL};
        execve(path, param, NULL);
        printf("Command Not Found!\n");
        exit(EXIT_FAILURE);
      }
    }
    wait(NULL);
  }
}