#include <sys/wait.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include "mytoc.h"

void freearray(char**ar){
  int i;
  for(i = 0; ar[i] != 0; i++){
    free(ar[i]);
  }
  free(ar);
}

char* concat(char* str1, char* str2){
  
  int str1length = findLength(str1);
  int str2length = findLength(str2);
  char* result = (char*)malloc(sizeof(char)*(str1length + str2length +1));
  int count = 0;
  for(int i = 0; i < str1length; i++){
    result[count] = str1[i];
    count++;
  }
  for(int i = 0; i < str2length; i++){
    result[count] = str2[i];
    count++;
  }
  result[count] = 0;
   return result;
}

char* copystr(char * str){
  int strlength = findLength(str);
  char * newstr = (char*) malloc(sizeof(char*)*(strlength+1));
  int i;
  for(i = 0; str[i] != 0; i++){
    if(str[i] == '\n')
      break;
    newstr[i] = str[i];
  }
  newstr[i] = 0;
  return newstr;
}

//compare two strings. return 1 if the strings are different and 0 if they are the same
int compare(char * str1, char * str2){
  int i;
  int str1length = findLength(str1);
  int str2length = findLength(str2);
  if(str1length != str2length)
    return 1;
  for(i = 0; str1[i] != 0; i++)
    if(str1[i] != str2[i])
      return 1;
  return 0;
}

int execMethod(int argc, char ** argv, char ** envp){
  int retVal = execve(argc,&argv[0],envp);
  printf("Program terminated with exit code %d\n", retVal);
  return 0;
}

int main(int argc, char**argv, char**en){
  char* command, *param[127];
  char * cmd;
  while(1){
    
    printf("$ ");
    char str[1024];
    fgets(str, 1000, stdin);
    //printf("str = %s", str);
    char** list = mytoc(str, ' ');
    int i;
    if(findLength(str) > 1){
      if(list[0] == "cd\0"){
	int changed = chdir(list[1]);
	if(changed == 0)
	  printf("Error: could not change directory.\n");
      }
      
      for(i = 0; list[i] != 0; i++)
	param[i] = copystr(list[i]);
      param[i]=0;
      if(compare(param[0], "exit") == 0)
	break;
      if(fork() != 0)
	wait(NULL);
      else{
	if(param[0][0] == '/'){
	  execMethod(param[0], param, en);
	}
	else{
	  param[0] = concat("/bin/\0", param[0]);
	  execMethod(param[0], param, en);
	}
      }
      //freearray(list);
      cmd = 0;
    }
    str[0] = 0;
  }
  return 0;
}
