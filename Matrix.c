#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct Matrix__{
//The name of the matrix, useful
char* Name;
//Number of rows of matrix
long long int Rows;
//
////Number of columns of matrix
long long int Columns;
//
////All entries of matrix, 2D!!!!!!!
long double ** Entries;
//
} Matrix;

//Add two matrices, return nothing, A is new matrix
void AddM(Matrix* A, Matrix * B, long double Mult,char*Name);
//Add two matrices, return new matrix C
Matrix* AddMR(Matrix* A, Matrix* B, long double Mult,char*Name);
//Inverse of Matrix, Set A to inverse,
void InverseM(Matrix* A,char*Name);
//Transpose itself matrix
void TransposeM(Matrix* A,char*Name);
//Transpose matrix, return transposed matrix
Matrix* TransposeMR(Matrix*,char*Name);
//Set A to power of itself
void PowerM(Matrix* A,long long int Power,char*N);
//Return Power of Matrix A
Matrix* PowerMR(Matrix* A,long long int Power,char*N);
//Inverse of Matrix, Returned
Matrix * InverseMR(Matrix* A,char*N);
//Copy Matrix, ALWAYS RETURNED
Matrix * CopyMatrixMR(Matrix* A,char*N);
//Get RREF for A Matrix
Matrix* RREFMR(Matrix* A,char*N);
//Multiply two matrices, return nothing, A is new matrix
void MultiplyM(Matrix* A, Matrix* B,char*N);
//Multiply two matrices, return new matrix C
Matrix * MultiplyMR(Matrix* A, Matrix* B,char*N);
//Multiply Row by value
void MultiplyRowM(Matrix* M,long long int Row, long double Value,char*N);


//Create Matrix given double[][] 2d array, obviously return this
//new matrix
Matrix* CreateMR(long double** e,int Rows,int Columns,char*N);
//Delete all matrices
void DeleteMatrixM(Matrix * M);
//Delete all doubles
void DeleteEntries(long double**E,long long int rows);


//Sigmoid
void SigmoidM(Matrix* A);
//Relu
void ReluM(Matrix* A);
//SoftMAx
void SoftMaxM(Matrix* A);
//Mimic DSigmoid
void DSigmoidM(Matrix* A);
//Mimic DRelu
void DReluM(Matrix* A);
//Mimic Deriv
void DSoftMaxM(Matrix*A);


//Print out name of matrix followed by all of its entries
void toString(Matrix* A);

//DYNAMICALLY OR NORMALLY Reads matrix from file, returns Matrix Created
//Matrix* ReadMR(char* FileName,char Delimiter);

Matrix* ReadFile(char* FileName,char Delimiter);

void SaveMatrix(Matrix* M, char* FileName);

void WriteFile(FILE* F,Matrix* M);

long long int GetColumns(FILE* F);

long double* NextDouble(FILE* F,char D);

//bool DelimiterNext(FILE* F,char Delim);

/**
 * Matrix testing main
 */
int main(int argc, char** argv){
//Matrix* M = malloc(sizeof(Matrix));
printf("\n LONG Double is size of:%lu\nDouble is size of:%lu\nLONG INT SIZE:%lu\nINT SIZE:%lu",sizeof(long double),sizeof(double),sizeof(long long int),sizeof(int));

long double D = 0.00000001000000000000001111111111;
long long int i = 10000000000000000000000;

printf("\n LONG DOUBLE:%LG",D);
printf("\nLONG INT:%lld",i);

Matrix* NewM = ReadFile("M1",'_');

NewM->Name = "HEYA";

toString(NewM);

SaveMatrix(NewM,"MyM");

DeleteMatrixM(NewM);







return 0;
}

//Add two matrices, return nothing, A is new matrix
void AddM(Matrix* A, Matrix * B, long double Mult,char*Name){
if(A==NULL||B==NULL){
printf("\n NULL MATRIX TO AddM");
exit(0);
}

if(A->Rows!=B->Rows && A->Columns!=B->Columns){
printf("\n ROWS DON'T MATCH COLUMNS!");
return;
}

long long int i=0;
long long int j=0;
for(i=0;i<A->Rows;i+=1){
for(j=0;j<B->Columns;j+=1){
A->Entries[i][j]+=Mult*B->Entries[i][j];
}
}

A->Name=Name;

}////Add two matrices, return new matr

Matrix* AddMR(Matrix* A, Matrix* B, long double Mult,char*Name){
if(A==NULL||B==NULL){
printf("\n NULL MATRIX TO AddMR");
exit(0);
}

if(A->Rows!=B->Rows && A->Columns!=B->Columns){
printf("\n ROWS DON'T MATCH COLUMNS!");
return NULL;
}

long double** Entries = malloc(A->Rows*sizeof(long double*));

long long int i=0;
long long int j=0;
for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(B->Columns*sizeof(long double));
for(j=0;j<B->Columns;j+=1){
Entries[i][j]=A->Entries[i][j]+(Mult*B->Entries[i][j]);
}
}

Matrix* C = malloc(sizeof(Matrix));
C->Rows = A->Rows;
C->Columns = B->Columns;
C->Entries = Entries;
C->Name = Name;

return C;
}////Inverse of Matrix, Set A to inverse,
void InverseM(Matrix* A,char*Name){

}////Transpose itself matrix
void TransposeM(Matrix* A,char*Name){
if(A==NULL){
printf("\n NULL MATRIX TO TRANSPOSE");
exit(0);
}

long long int i=0;
long long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j]=A->Entries[j][i];
}
}

A->Name=Name;

}////Transpose matrix, return transposed matrix

Matrix* TransposeMR(Matrix* A,char*Name){
if(A==NULL){
printf("\nNULL Matrix to TransposeMR");
exit(0);
}

long double** Entries = malloc(A->Columns*sizeof(long double*));

long long int i=0;
long long int j=0;

for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(A->Rows*sizeof(long double));
for(j=0;j<A->Columns;j+=1){
Entries[j][i]=A->Entries[i][j];
}
}

Matrix* B = malloc(sizeof(Matrix));
B->Rows = A->Columns;
B->Columns=A->Rows;
B->Entries=Entries;
B->Name=Name;

return B;
}

////Set A to power of itself
void PowerM(Matrix* A,long long int Power,char*Name){

}////Return Power of Matrix A

Matrix* PowerMR(Matrix* A,long long int Power,char*Name){
return NULL;
}////Inverse of Matrix, Returned

Matrix * InverseMR(Matrix* A,char*Name){
return NULL;
}////Copy Matrix, ALWAYS RETURNED

Matrix * CopyMatrixMR(Matrix* A,char*Name){
if(A==NULL){
printf("\nNo matrix to copy");
exit(0);
}
Matrix * C = malloc(sizeof(Matrix));
long double** Entries = malloc(A->Rows*sizeof(long double*));
if(Entries==NULL){
printf("\n CopyMatrixMR Entries NULL");
exit(0);
}
long long int i=0;
long long int j=0;
for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(A->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lld} NULL CopyMR",i);
exit(0);
}
for(j=0;j<A->Columns;j+=1){
Entries[i][j]=A->Entries[i][j];
}
}
C->Rows=A->Rows;
C->Columns=A->Columns;
C->Entries=A->Entries;
C->Name=Name;
return C;
}////Get RREF for A Matrix

Matrix* RREFMR(Matrix* A,char*Name){
return NULL;
}

////Multiply two matrices, return nothing, A is new matrix
void MultiplyM(Matrix* A, Matrix* B,char*Name){
if(A==NULL||B==NULL){
printf("\n  NULL Matrix A Columns does not match Matris B Rows");
exit(0);
}
if(A->Columns!=B->Rows){
printf("\n Matrix A Columns does not match Matris B Rows");
return;
}

long double**Entries = malloc(A->Rows*sizeof(long double*));
if(Entries==NULL){
printf("\n MultiplyM Entries NULL");
exit(0);
}
long long int i=0;
long long int j=0;
long long int l=0;
long double sum=0;

for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(B->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lld} NULL MultiplyM",i);
exit(0);
}
for(j=0;j<B->Columns;j+=1){
sum = 0.0;
for(l=0;l<A->Columns;l+=1){
sum+=A->Entries[i][l]*B->Entries[l][j];
}
Entries[i][j]=sum;
}
}

DeleteEntries(A->Entries,A->Rows);
A->Name=Name;
A->Columns=B->Columns;

}////Multiply two matrices, return new matrix C

Matrix * MultiplyMR(Matrix* A, Matrix* B,char*Name){
if(A==NULL||B==NULL){
printf("\n  NULL Matrix A Columns does not match Matris B Rows");
exit(0);
}
if(A->Columns!=B->Rows){
printf("\n Matrix A Columns does not match Matris B Rows");
return NULL;
}

long double**Entries = malloc(A->Rows*sizeof(long double*));
if(Entries==NULL){
printf("\n MultiplyMR Entries NULL");
exit(0);
}
long long int i=0;
long long int j=0;
long long int l=0;
long double sum=0;

for(i=0;i<A->Rows;i+=1){
Entries[i] = malloc(B->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lld} NULL MultiplyMR",i);
exit(0);
}
for(j=0;j<B->Columns;j+=1){
sum = 0.0;
for(l=0;l<A->Columns;l+=1){
sum+=A->Entries[i][l]*B->Entries[l][j];
}
Entries[i][j]=sum;
}
}

Matrix* C = malloc(sizeof(Matrix));
if(C==NULL){
printf("\n MultiplyMR NULL Created Matrix");
exit(0);
}
C->Name=Name;
C->Entries=Entries;
C->Rows=A->Rows;
C->Columns=B->Columns;

return C;
}////Multiply Row by value
void MultiplyRowM(Matrix* M,long long int Row, long double Value,char*Name){
if(M==NULL){
printf("\n MuitiplyRowM NULL Matrix");
exit(0);
}
if(Row>=M->Rows || Row<0){
printf("\nInvalid Row MultiplyRowM");
exit(0);
}
long long int j=0;
for(j=0;j<M->Columns;j+=1){
M->Entries[Row][j]*=Value;
}
M->Name = "Mult";
}
////Create Matrix given double[][] 2d array, obviously return this
////new matrix
Matrix* CreateMR(long double** E,int Rows,int Columns,char*Name){
if(E==NULL){
printf("\nCreateMR NULL Entries");
exit(0);
}
if(Rows<=0 || Columns <=0){
printf("\nInvalid Rows/Columns CreateMR");
exit(0);
}
Matrix* M = malloc(sizeof(Matrix));
M->Entries = E;
M->Name = Name;
M->Rows=Rows;
M->Columns=Columns;
return M;
}
////Delete all matrices
void DeleteMatrixM(Matrix * M){
if(M==NULL){
printf("\n MATRIX TO DELETE IS NULLED\n");
exit(-3);
}

DeleteEntries(M->Entries,M->Rows);

free(M);
M=NULL;
}
////Delete all doubles
void DeleteEntries(long double**E,long long int Rows){
long long int i=0;
for(i=0;i<Rows;i+=1){
free(E[i]);
E[i]=NULL;
}
free(E);
E=NULL;
}
//
////Sigmoid
void SigmoidM(Matrix* A){
if(A==NULL){
printf("\n No Matrix to Sigmoid");
exit(0);
}

long long int i=0;
long long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j] = 1/(1+expl(-A->Entries[i][j]);
}
}

}

////Relu
void ReluM(Matrix* A){
if(A==NULL){
printf("\n No Matrix to Relu");
exit(0);
}

long long int i=0;
long long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
if(A->Entries[i][j]<=0){
A->Entries[i][j]=0.0;
}
}
}

}

//SoftMAx
void SoftMaxM(Matrix* A){

}

//Mimic DSigmoid
void DSigmoidM(Matrix* A){

}

//Mimic DRelu
void DReluM(Matrix* A){

}

//Mimic Deriv
void DSoftMaxM(Matrix*A){

}

////Print out name of matrix followed by all of its entries
void toString(Matrix* A){
printf("\n%s\n ROWS:%lld COLUMNS:%lld\n",A->Name,A->Rows,A->Columns);
long long int i=0;
long long int j=0;
   for(i=0;i<A->Rows;i+=1){
	for(j=0;j<A->Columns;j+=1){
	   printf("%LG ",A->Entries[i][j]);
	}
	printf("\n");
   }

}//

//Iterate until reach new line, this will be column
//MUST DEFINE COLUMN AT THE FIRST ROW AT LEAST!!!!!!!!!!
long long int GetColumns(FILE* F){

long PrevPosition = ftell(F);

long long int C = 0;

bool Dot = false;

char c;

while(fscanf(F,"%c",&c)!=EOF){
if(!isdigit(c)){

if(c=='.'){
if(Dot==true){
printf("\n DOUBLE DOTS!!!\n");
Dot=false;
continue;
//exit(-1);
}
Dot=true;
}

else{
Dot=false;

if(c==' ')
C+=1;

if(c=='\n'){
printf("\n Made it to final column:%lld\n",C);
break;
}

}

}
/*else{





}
*/
}

//fsetpos(F,PrevPosition);
fseek(F,PrevPosition,SEEK_SET);

return C;

}

//Get Next long double if double, return double, if not return NULL
//If end of file, return -999999999 ld*
//Returns two ld
//first is 0 for a num
//second is 1 for delimiter and a num
//third is 2 for EOF
long double* NextDouble(FILE*F,char Delimiter){

bool Dot = false;

//long double Num = -999999999;

long double* Ret = malloc(2*sizeof(long double));
//long long int Line = 0;
Ret[1] = -88888888;

int ASize = 1;
char* app = malloc(ASize*sizeof(char));
app[0]='\0';

char c;

while(fscanf(F,"%c",&c)!=EOF){
printf("\nCHAR:%c\n",c);
printf("\n NUM:%s\n",app);
if(!isdigit(c)){
if(c=='.'){
if(Dot){
printf("TWO DOTS IN A DOUBLE NOT ALLOWED!:%s @ LINE:%ld",app,ftell(F));
exit(-1);
}

app=realloc(app,(ASize++)*sizeof(char));
app[ASize-2] = c;

Dot=true;
}
else if(c==Delimiter){
//Delimiter hit, break away return NULL
//long double D = 0.0;

sscanf(app,"%LG",&Ret[1]);

Ret[0] = 1;
//Ret[1] = D;
free(app);
return Ret;
}
//else if(c==' '){
//continue;
//}
else{
//if not digit, not., not delimiter
//long double D = 1.0;

sscanf(app,"%LG",&Ret[1]);

Ret[0] = 0;
//Ret[1]=D;
free(app);
return Ret;
}
}
else{

app=realloc(app,(ASize++)*sizeof(char));

app[ASize-2] = c;

}

}

//reached EOF, retu
//long double* LD = malloc(sizeof(long double));

*Ret = 2;
*(Ret+1)=-999999999;
free(app);
return Ret;
}

/**
 *Read File, store into matrix
 */
Matrix* ReadFile(char* FileName,char Delimiter){
FILE* F = fopen(FileName,"r");
if(F==NULL){
printf("\nUnable to open file:%s",FileName);
exit(-4);
}

long long int COLUMNS = GetColumns(F)+1;

long long int Columns = 0;
long long int Rows = 0;

long long int Size = 1;
long double ** Entries = malloc(1*sizeof(long double *));
Entries[0] = malloc((COLUMNS)*sizeof(long double));

while(true){

long double * Result = NextDouble(F,Delimiter);

if(Result[0]==2||Result[0]==1){


if(Result[0]==1){
if(Result[1]!=-88888888){
printf("\n RESULT FINAL:%LG",Result[1]);
Entries[Rows][Columns]=Result[1];
}
}

free(Result);
Result=NULL;

printf("\n DONE READING");
break;
}

printf("\n CASE: %LG",Result[0]);

printf("\n ENTRY: %LG [%lld,%lld] CASE:%LG",Result[1],Rows,Columns,Result[0]);

if(Result[1]!=-88888888){
//Columns+=1;
if(Columns>=COLUMNS){
Columns=0;
Rows+=1;

}
//
if(Rows>=Size){
Size+=1;
Entries[Rows] = malloc((COLUMNS)*sizeof(long double));
}
//
Entries[Rows][Columns] = Result[1];
//
Columns+=1;
}
free(Result);
Result=NULL;
}

//Num Rows and Columns to store all values
//
printf("\n ROWS:%lld COLUMNS:%lld\n",++Rows,COLUMNS);
//
long long int j=0;
long long int k=0;
for(j=0; j<Rows;j+=1){
        for(k=0; k<COLUMNS;k+=1){
                        printf("%LG ",Entries[j][k]);
                                }
                                        printf("\n");
}

Matrix* M = malloc(sizeof(Matrix));
M->Rows = Rows;
M->Columns=COLUMNS;

M->Entries = Entries;

fclose(F);

return M;
}
//fseek(F,PrevPosition,SEEK_SET);
//

void SaveMatrix(Matrix*M,char* FileName){
if(M==NULL){
printf("\n No matrix to Save");
return;
}

if(access(FileName,F_OK)!=-1){
//File Exists
printf("\n File:%s Exists\nOverWrite? >=1 Yes <=0 No:",FileName);
int i;
scanf("%d",&i);
if(i>=1){
FILE* F = fopen(FileName,"w+");
WriteFile(F,M);
fclose(F);
}
}
else{
FILE* F = fopen(FileName,"w+");
WriteFile(F,M);
fclose(F);
}
}

//Writes to file regardless of position
void WriteFile(FILE* F, Matrix* M){

long long int i=0;
long long int j=0;
fprintf(F,"\n%s\n",M->Name);
fprintf(F,"%lld\n",M->Rows);
fprintf(F,"%lld\n",M->Columns);
for(i=0; i<M->Rows;i+=1){
for(j=0; j<M->Columns;j+=1){
fprintf(F,"%LG ",M->Entries[i][j]);
}
fprintf(F,"\n");
}

}
