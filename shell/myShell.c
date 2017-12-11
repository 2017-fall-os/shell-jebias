#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include "mytoc.h"

char *output = "$ ";

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
  //if(str1length != str2length)
  //   return 1;
  for(i = 0; str2[i] != 0; i++)
    if(str1[i] != str2[i])
      return 1;
  return 0;
}

int arrayHas(char* str, char c){
  int i;
  for(i = 0; str[i] != 0; i++){
    if(str[i] == c)
      return 1;
  }

  return 0;
}

int execMethod(char* argc, char ** argv, char ** envp){
  /*
  //find number of pipes
  for(j = 0; list[j] != 0; j++){
	if(arrayHas(list[j], '|'))
	  numOfPipes++;
      }

  if(numOfPipes > 0){
    int fd[2];
    int d0 = dup(0);
    int d1 = dup(1);

    
    
    for(int k = 0; k < numOfPipes - 1; k++){
      pid = fork();
      if(pid == 0)
	}
  }
  */
  int retVal = execve(argv[0],&argv[0],envp);
  printf("Program terminated with exit code %d\n", retVal);
  return 0;
}

int countWords(char**list){
  int i;
  for(i = 0; list[i] != 0; i++);
  return i;
}
/*
char** getPath(char**en){
  int key;
  char **path;
  char **temp;  
  for(key = 0; compare(en[key], "PATH\0") == 0; key++ );
  temp = mytoc(en[key], '=');
  path = mytoc(temp[1], ':');
  for(key = 0; compare(en[key], "PS1\0") == 0; key++);
  int len = countWords(temp);
  output = (char*)malloc(sizeof(char)*(findLength(temp[1]+1)));
  for(key = 0; key < findLength(temp[1]); key++)
    output[key] = temp[1][key];
  output[key] = 0;
  
  temp[0] = 0;

  return path;
}
*/
int main(int argc, char**argv, char**en){
  char* command, *param[127];
  char * cmd;
   char str[1024];
  
  while(1){
    // printf("$ ");
    printf("%s", output);
    char c = getchar();
    int charCount = 0;
    str[charCount] = c;
    charCount++;
    while(c >= 32){
      c = getchar();
      str[charCount] = c;
      charCount++;
    }
    
      //scanf("%s", str);
    //fgets(str, 1000, stdin);
    //printf("str = %s\n", str);
    char** list = mytoc(str, ' ');
    int i;
    int j;
    //int lastCharIsSpace = 0;
    //for(i = 0; str[i] != 0; i++);
    //printf("str[i-2] = %c\n",str[i-2]);
    //if(str[i-2] == ' '){
      
    // lastCharIsSpace = 1;
    // }
    //    int numOfPipes = 0;
    //pipeFds[2];
    //pipe(pipeFds);

    if(findLength(str) > 1){
      if(list[0] == "cd\0"){
	int changed = chdir(list[1]);
	if(changed == 0)
	  printf("Error: could not change directory.\n");
      }
      //printf("%s\n",list[1]);
       
      for(i = 0; list[i] >= 32; i++){
	//	printf("i = %d\n", i);
	param[i] = copystr(list[i]);
      }
      param[i-1] = 0;
      //printf("lastchar is = %d\n",lastCharIsSpace);
      /* if(lastCharIsSpace == 1){
	printf("im here");
	param[i-1] = 0;
	printf("is 1\n");
	}*/
      
      //  printList(param);
      // for(i = 0; list[i] != 0; i++)
      //	printf("param[%d] = %s\n", i, param[i]);
      // printf("number of pipes = %d\n",numOfPipes);
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
