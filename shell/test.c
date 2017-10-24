#include<stdio.h>
//#include<unistd.h>
#include<stdlib.h>
#include "mytoc.h"

char* pathName(){
  /*const*/ char* s = getenv("PATH");
  if(s != NULL)
    return s;
  else
    return "getenv returned NULL";
}

void forkMethod(char**list, char**envp){
  int count = 0;
  int f = fork();
    if(f < 0){ //fork failed
      fprintf(stderr, "fork failed");
      exit(1);
    }
    else if(f == 0){
      if(list[0][0] == '/'){
      int count = 0; //used to count the size of the arguement at list[0]
      for(int i = 0;list[0][i] != 0; i++){
	count++;
      }
       list[0][count-1] = '\0';//for some reason there was always a space after the arguement, so I just got rid of the space
  //char**envList = {"HOME=/student", PATH="/bin:/sbin", NULL};
    execve(list[0], &list[0], envp);
      }
      else{
	system(list[0]);
      }
    }
    else{
      int w = wait(NULL);
      // printf("Hello, I am parent of %d (w:%d) (pid:%d)\n", f, w, (int) getpid());
    }
}

int main(int argc, char**argv, char**envp){
  char str[1000];
  //system("/bin/cat /etc/passwd");
  //printf("%s\n", pathName());
  while(1){
    printf("$ ");
    fgets(str, 1000, stdin);
    char** list = mytoc(str, ' ');
    forkMethod(list, envp);
  
   
  
  }
  return 0;
}
