//#include <"string.h">
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>


//Points to concatenated String!
typedef struct String_{
//
////Length of String
int Length;
//
char* Name;
//
}String;

String* Concat(String* s1, char* s2);

void PrintString(String* s);

void DeleteString(String* s);

/*
int main(int argc, char** argv){
String* s = Concat(NULL,"HIYA");
//PrintString(s);

Concat(s,"-HIYA2");

//printf("\n%s",s);
//PrintString(s);

DeleteString(s);
}
*/

void PrintString(String* s){
if(s!=NULL)
printf("%s",s->Name);
else
printf("(null)");
}

//Concat String object with string literal
String* Concat(String* s1, char*s2){
String* s = NULL;
if(s1==NULL){
s = malloc(sizeof(String));
}
else
s=s1;
if(s2==NULL){
printf("\nMust enter some string");
exit(-1);
}
int l1 = s->Name==NULL? 0:strlen(s->Name);

char* c = malloc(l1+1+strlen(s2)*sizeof(char));

if(l1>0)
strncat(c,s->Name,l1);
strncat(c,s2,strlen(s2));

s->Name=c;

s->Length=strlen(s->Name);
return s;
}

void DeleteString(String* s){
if(s!=NULL){
if(s->Name!=NULL)
free(s->Name);
free(s);
}
}
