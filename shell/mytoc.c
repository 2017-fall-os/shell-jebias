#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "mytoc.h"




void printList(char**list){
  int i;
  int j;
  for(i = 0; list[i] != 0; i++){
    for(j = 0; list[i][j] != 0; j++){
      printf("%c", list[i][j]);
    }
    printf("\n");
  }
}

//function that is used to tell me how many words are in a string while using the delimiter
int numberOfWords(char *str, char delim){
  int numOfWords = 0;
  int word = 0;
  int space = 0;
  int i;
  for(i = 0; str[i] != 0; i++){
    //check for word
    if(str[i] != delim){
      //printf("there is a word\n");
      word = 1;
    }
    //check for space
    if(str[i] == delim){
      space = 1;
      //check if there was a word before the delim
      if(word == 1){
	numOfWords++;
	word = 0;
      }
    }
    //check if the string ends with a word
    if(str[i+1] == 0){
      if(word == 1)
	numOfWords++;
    }
  }
  return numOfWords;
}

//tells me the number of characters in a string
int numberOfChar(char *word){
  int p;
  int count = 0;
  for(p = 0; word[p] != 0; p++)
    count++;
  return count;
}

void eraseSpace(char*word){
  int i;
  if(findLength(word) > 1){
    for(i = 0; word[i] != 0; i++);
    word[i-1] = 0;
  }
}

int findLength(char* str){
  int i;
  //printf("str in findlength = %s\n", str);
  for(i = 0;(str[i] != 0 || str[i] != '\0'); i++)
    if(str[i] == '\n')
      break;
  return i;
}

//given a strin and a delimiter, it returns an array of strings with the appropriate memory allocated
char ** mytoc(char *str, char delim){
  char **listOfWords;
  int words = numberOfWords(str, delim);
  listOfWords = (char**)calloc(words,sizeof(char*));
  int i, j;
  int word = 0;
  int space = 0;
  int count = 0;
  int letters = 0;
  int startOfWord = 0;
  
  for(i = 0; str[i] != 0; i++){
    
    //check for word
    if(str[i] != delim){
      if(space == 1){
	startOfWord = i;
      }
      word = 1;
      space = 0;
      letters++;
    }

    //check for space
    if(str[i] == delim){
      space = 1;
      //check if there was a word before the delim
      if(word == 1){
	listOfWords[count] = (char *)malloc(letters);

	for(j = 0; j < letters; j++){
	  listOfWords[count][j] = str[startOfWord + j];
	}
	word = 0;
	count++;
	letters = 0;
      
      }else{
	letters = 0;
      }
    }
    //check if the string ends with a word
    if(str[i+1] == 0){
      if(word == 1){
	listOfWords[count] = (char *)malloc(letters);
	for(j = 0; j < letters; j++){
	  listOfWords[count][j] = str[startOfWord + j];
	}
	listOfWords[count][j-1] = 0;
	listOfWords[count+1] = 0;

	
      }
      else{
	
	listOfWords[count] = 0;
      }
    }
    
  }
  return listOfWords;
}  
