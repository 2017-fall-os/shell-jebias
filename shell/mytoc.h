#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

char ** mytoc(char *str, char delim);
int numberOfWords(char *str, char delim);
int numberOfChar(char *word);
int findLength(char* str);
void eraseSpace(char* word);
