/*
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
#include "String.c"
#include <ctype.h>
#include <math.h>
*/

#include "String.c"

/*
//Points to concatenated String!
typedef struct String_{

//Length of String
int Length;

char* Name;

}String;
*/

typedef struct Data_{

long double Entry;

struct Data_* Next;

}Data;

void PrintEntries(Data **D,size_t Len);

typedef struct Matrix__{
//The name of the matrix, useful
char* Name;
//Number of rows of matrix
size_t Rows;
//
////Number of columns of matrix
size_t Columns;
//
////All entries of matrix, 2D!!!!!!!
long double ** Entries;
//
} Matrix;

typedef struct MFS_{
//Name of file stream
char* FileName;
//To be closed only when reach EOF!!!
FILE* F;
//Matrix returned from each parse
Matrix* M;

}MatrixFileStream;

//Matrix FILE Stream structure
/////////////////////////////////////////////////////////////////////////////////////
//Close file, not delete matrix
void CloseMFS(MatrixFileStream* MFS);
//Open file, return stream obj
MatrixFileStream* NewMatrixFileStream(char* Name);
/////////////////////////////////////////////////////////////////////////////////////


Matrix* MNew = NULL;

//Matrix OPERATIONS!!!
/////////////////////////////////////////////////////////////////////////////////////
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

void RandomizeM(Matrix* A);

void RREFM(Matrix* A, char*N);

//Multiply two matrices, return nothing, A is new matrix
void MultiplyM(Matrix* A, Matrix* B,char*N);
//Multiply two matrices, return new matrix C
Matrix * MultiplyMR(Matrix* A, Matrix* B,char*N);

//Multiply across two matrices affecting first matrix
void MultiplyAcrossM(Matrix* A, Matrix*B, char* N);

//Multiply Across matrix with value
void MultiplyAcrossV(Matrix*A,long double Lr);

//Multiply across two matrices  and return new matrix
Matrix* MultiplyAcrossMR(Matrix*A, Matrix* B, char* N);

//Get sum of norm values, return norm matrix, which are all from Matrix A...
Matrix * NormalizeValuesMR(Matrix*A);
//Normalize Matrix given its normalize values
void NormalizeM(Matrix* A, Matrix*Norms,bool Transposed);

//Remove bias from matrix
Matrix* NoBiasMR(Matrix*A);

//Append Bias to existing entries
Matrix* AppendBiasM(Matrix*A);

//Multiply Row by value
void MultiplyRowM(Matrix* M,unsigned long int Row, long double Value);
//Add Row by vakue
void AddRowM(Matrix* M, unsigned long int Column,unsigned long int Column2, long double Value);
/////////////////////////////////////////////////////////////////////////////////////

//Matrix Data Creation/Deletion
///////////////////////////////////////////////////////////////////////////////////
//Create double** entries
long double** CreateE(/*long double**e,*/size_t Rows,size_t Columns);
//Create Matrix given double[][] 2d array, obviously return this
//new matrix
Matrix* CreateMR(long double** e,size_t Rows,size_t Columns,char*N);
//Delete all matrices
void DeleteMatrixM(Matrix * M);
//Delete all doubles
void DeleteEntries(long double**E,unsigned long int rows);
///////////////////////////////////////////////////////////////////////////////////

//ACTIVATION FUNCTIONS AND DERIVATIVE OPERATIONS
/////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////

//Print out name of matrix followed by all of its entries
void toString(Matrix* A);

//DYNAMICALLY OR NORMALLY Reads matrix from file, returns Matrix Created
//Matrix* ReadMR(char* FileName,char Delimiter);

//FILE* INPUT = NULL;

//FILE MATRIX HANDLING
//////////////////////////////////////////////////////////////////////////////////
MatrixFileStream* ReadFile(MatrixFileStream*MFS,char Delimiter);

void SaveMatrix(Matrix* M, FILE* F);

void WriteFile(FILE* F,Matrix* M);

size_t GetColumns(FILE* F);

size_t GetRows(FILE* F,char Delim);

typedef struct RetCase_{

long double First;
long double Second;

}Ret;


Data * AllEntries = NULL;
void AddEntry(Data** E, long double d);
void DeleteAllEntries(Data** E,size_t Len);


Ret* NextDouble(FILE* F,char D);
//////////////////////////////////////////////////////////////////////////////////

//Const
Ret R[1];

void NextLine(FILE* F);

char* NextString(FILE*F,char D);

//long double* Ret = NULL;

//bool DelimiterNext(FILE* F,char Delim);

/**
 * Matrix testing main
 */

/*
int main(int argc, char** argv){
//Matrix* M = malloc(sizeof(Matrix));
printf("\n LONG Double is size of:%lu\nDouble is size of:%lu\nLONG INT SIZE:%lu\nINT SIZE:%lu",sizeof(long double),sizeof(double),sizeof(unsigned long int),sizeof(int));

long double D = 0.00000001000000000000001111111111;
unsigned long int i = 10000000000000000000000;

printf("\n LONG DOUBLE:%Lf",D);
printf("\nLONG INT:%lu",i);

MatrixFileStream* MFS1 = NewMatrixFileStream("M1");//malloc(sizeof(MatrixFileStream));
MatrixFileStream* MFS2 = NewMatrixFileStream("M2");//malloc(sizeof(MatrixFileStream));

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);

CloseMFS(MFS1);

CloseMFS(MFS2);

MFS1 = NewMatrixFileStream("M1T1");

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);

ReadFile(MFS1,'_');

DeleteMatrixM(MFS1->M);


return 0;

ReadFile(MFS2,'_');

CloseMFS(MFS1);
CloseMFS(MFS2);

Matrix* M1 = MFS1->M;

Matrix* M2 = MFS2->M;

M1->Name = "HEYA";

M2->Name = "HEYA 22";

toString(M1);

toString(M2);

AddM(M1,M2,1.0,"M1+M2");

toString(M1);

MultiplyM(M1,M2,"M1 * M");

toString(M1);

Matrix* INV = InverseMR(M1,"Inverse M1");

toString(INV);

toString(M1);

M1->Entries[0][2] = 5.5555;

TransposeM(M1,"M1 Transpose");

toString(M1);

PowerM(M1,2,"Power Matrix");

toString(M1);

DeleteMatrixM(INV);
DeleteMatrixM(M1);
DeleteMatrixM(M2);

return 0;

}
*/

//Add two matrices, return nothing, A is new matrix
void AddM(Matrix* A, Matrix * B, long double Mult,char*Name){
if(A==NULL||B==NULL){
printf("\n NULL MATRIX TO AddM");
exit(0);
}

if(A->Rows!=B->Rows && A->Columns!=B->Columns){
printf("\n ROWS DON'T MATCH COLUMNS!");
exit(-1);
//return;
}

size_t i=0;
size_t j=0;
for(i=0;i<A->Rows;i+=1){
for(j=0;j<B->Columns;j+=1){
A->Entries[i][j]+= Mult * (B->Entries[i][j]);
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

unsigned long int i=0;
unsigned long int j=0;
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
if(A==NULL){
printf("\n NULL MAtrix Given for inverse!");
exit(-2);
}

if(A->Rows!=A->Columns){
printf("\n Matrix Rows must match columns for inverse matrix");
return;
}

//Matrix* A = CopyMatrixMR(B,"Matrix B Copy");

unsigned long int i=0;
unsigned long int j=0;
unsigned long int k=0;

double divisor = 1.0;
Matrix* EMatrix = RREFMR(A,"Echelon Matrix");
for(i=0;i<A->Columns;i+=1){
for(j=0;j<A->Columns;j+=1){
if(i==j){
if(A->Entries[i][j]!=1.0){
divisor  =A->Entries[i][j];
if(divisor!=0.0){
MultiplyRowM(A,i,1.0/divisor);
MultiplyRowM(EMatrix,i,1.0/divisor);
}
else{
printf("\n CANNOT REDUCE COLUMN:%lu",i);
return;
}
}
k=0;
while(k<A->Columns){
if(k!=j){
if(A->Entries[j][k]<0||A->Entries[j][k]>0){
AddRowM(A,i,k,-A->Entries[j][k]);
AddRowM(EMatrix,i,k,-EMatrix->Entries[j][k]);
}
}
if(A->Entries[j][j]!=1.0){
divisor = A->Entries[j][j];
if(divisor!=0.0){
MultiplyRowM(A,j,1.0/divisor);
MultiplyRowM(EMatrix,j,1.0/divisor);
}
else{
printf("\n CANNOT REDUCE MATRIX");
return;
}
}
k++;
}
}
printf("\n Matrix NOW: \n");
toString(A);
printf("\n EMatrix NOW: \n");
toString(EMatrix);
}
}

DeleteEntries(A->Entries,A->Rows);

A->Entries = EMatrix->Entries;

free(EMatrix);
EMatrix=NULL;

A->Name =Name;
//return EMatrix;
}

////Transpose itself matrix
void TransposeM(Matrix* A,char*Name){
if(A==NULL){
printf("\n NULL MATRIX TO TRANSPOSE");
exit(0);
}

unsigned long int i=0;
unsigned long int j=0;

long double** TM = malloc(A->Columns*sizeof(long double*));
while(j<A->Columns){
TM[j]=malloc(A->Rows*sizeof(long double));
j+=1;
}

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
TM[j][i]=A->Entries[i][j];
}
}

DeleteEntries(A->Entries,A->Rows);
A->Entries=TM;

A->Name=Name;

}////Transpose matrix, return transposed matrix

Matrix* TransposeMR(Matrix* A,char*Name){
if(A==NULL){
printf("\nNULL Matrix to TransposeMR");
exit(0);
}

//long double** Entries = malloc(A->Columns*sizeof(long double*));
long double** Entries = CreateE(A->Columns,A->Rows);
if(Entries==NULL){
printf("\n BAD ENTRIES TRANSPOSE 1");
exit(-4);
}

unsigned long int i=0;
unsigned long int j=0;

printf("\n A Columns:%lu A Rows:%lu",A->Columns,A->Rows);

for(i=0;i<A->Rows;i+=1){
//Entries[i]=malloc(A->Rows*sizeof(long double));
/*
if(Entries[i]==NULL){
printf("\n BAD ENTRIES TRANSPOSE 2");
exit(-4);
}
*/
for(j=0;j<A->Columns;j+=1){
//Entries[j][i] = 0.0;

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
void PowerM(Matrix* B,long long int Power,char*Name){

if(B==NULL){
printf("\n PowerM No Matrix Given");
exit(-1);
}

if(B->Columns!=B->Rows){
printf("\n Matrix Columns != Matrix Rows PowerM");
exit(-1);
}
if(Power==0){

Matrix* RREF = RREFMR(B,"Power 0 Matrix");
DeleteEntries(B->Entries,B->Rows);
B->Entries=RREF->Entries;
free(RREF);
RREF=NULL;

}
else if(Power<0){

InverseM(B,"Inverse");

unsigned long int i=0;
Power=Power*-1;

for(i=0;i<Power;i+=1)
MultiplyM(B,B,"Inverse Powered");

}
else{

unsigned long int i=0;

for(i=0; i<Power;i+=1){
MultiplyM(B,B,"Matrix Powered");
}

}
}////Return Power of Matrix A

Matrix* PowerMR(Matrix* A,long long int Power,char*Name){

if(A==NULL){
printf("\n PowerMR No Matrix Given");
exit(-1);
}

Matrix* B = CopyMatrixMR(A,"PowerMR Copied Matrix");

if(B->Columns!=B->Rows){
printf("\n Matrix Columns != Matrix Rows PowerM");
exit(-1);
}
if(Power==0){

Matrix* RREF = RREFMR(B,"Power 0 Matrix");
DeleteEntries(B->Entries,B->Rows);
B->Entries=RREF->Entries;
free(RREF);
RREF=NULL;

}
else if(Power<0){

InverseM(B,"Inverse");

unsigned long int i=0;
Power=Power*-1;

for(i=0;i<Power;i+=1)
MultiplyM(B,B,"Inverse Powered");

}
else{

unsigned long int i=0;

for(i=0; i<Power;i+=1){
MultiplyM(B,B,"Matrix Powered");
}

}

return B;
}

////Inverse of Matrix, Returned
Matrix * InverseMR(Matrix* B,char*Name){

if(B==NULL){
printf("\n NULL MAtrix Given for inverse!");
exit(-2);
}

if(B->Rows!=B->Columns){
printf("\n Matrix Rows must match columns for inverse matrix");
return NULL;
}

Matrix* A = CopyMatrixMR(B,"Matrix B Copy");

unsigned long int i=0;
unsigned long int j=0;
unsigned long int k=0;

double divisor = 1.0;
Matrix* EMatrix = RREFMR(A,"Echelon Matrix");
for(i=0;i<A->Columns;i+=1){
for(j=0;j<A->Columns;j+=1){
if(i==j){
if(A->Entries[i][j]!=1.0){
divisor  =A->Entries[i][j];
if(divisor!=0.0){
MultiplyRowM(A,i,1.0/divisor);
MultiplyRowM(EMatrix,i,1.0/divisor);
}
else{
printf("\n CANNOT REDUCE COLUMN:%lu",i);
return NULL;
}
}
k=0;
while(k<A->Columns){
if(k!=j){
if(A->Entries[j][k]<0||A->Entries[j][k]>0){
AddRowM(A,i,k,-A->Entries[j][k]);
AddRowM(EMatrix,i,k,-EMatrix->Entries[j][k]);
}
}
if(A->Entries[j][j]!=1.0){
divisor = A->Entries[j][j];
if(divisor!=0.0){
MultiplyRowM(A,j,1.0/divisor);
MultiplyRowM(EMatrix,j,1.0/divisor);
}
else{
printf("\n CANNOT REDUCE MATRIX");
return NULL;
}
}
k++;
}
}
printf("\n Matrix NOW: \n");
toString(A);
printf("\n EMatrix NOW: \n");
toString(EMatrix);
}
}

EMatrix->Name =Name;
EMatrix->Rows=A->Columns;
EMatrix->Columns=A->Columns;

return EMatrix;
}

////Copy Matrix, ALWAYS RETURNED
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
unsigned long int i=0;
unsigned long int j=0;
for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(A->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lu} NULL CopyMR",i);
exit(0);
}
for(j=0;j<A->Columns;j+=1){
Entries[i][j]=A->Entries[i][j];
}
}

C->Rows=A->Rows;
C->Columns=A->Columns;
C->Entries=Entries;
C->Name=Name;

return C;
}

////Get RREF for A Matrix
void RREFM(Matrix*A,char*Name){

if(A==NULL){
printf("\n Matrix for RREF does not exist");
exit(-1);
}

if(A->Rows!=A->Columns){
printf("Matrix Rows does not match matrix columns for RREF");
exit(-1);
}

long double ** Entries = malloc(A->Columns*sizeof(long double*));

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Columns;i+=1){
Entries[i]=malloc(A->Columns*sizeof(long double));
for(j=0;j<A->Columns;j+=1){
if(i==j)
Entries[i][j] = 1.0;
else
Entries[i][j] = 0.0;
}
}


DeleteEntries(A->Entries,A->Rows);
A->Entries = Entries;

}

Matrix* RREFMR(Matrix* A,char*Name){
if(A==NULL){
printf("\n Matrix for RREF does not exist");
exit(-1);
}

if(A->Rows!=A->Columns){
printf("Matrix Rows does not match matrix columns for RREF");
exit(-1);
}

long double ** Entries = malloc(A->Columns*sizeof(long double*));

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Columns;i+=1){
Entries[i]=malloc(A->Columns*sizeof(long double));
for(j=0;j<A->Columns;j+=1){
if(i==j)
Entries[i][j] = 1.0;
else
Entries[i][j] = 0.0;
}
}

Matrix * EM = malloc(sizeof(Matrix));
EM->Name = Name;
EM->Rows = A->Columns;
EM->Columns = A->Columns;
EM->Entries = Entries;

return EM;
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
unsigned long int i=0;
unsigned long int j=0;
unsigned long int l=0;
long double sum=0;

for(i=0;i<A->Rows;i+=1){
Entries[i]=malloc(B->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lu} NULL MultiplyM",i);
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
A->Entries = Entries;
A->Name=Name;
A->Columns=B->Columns;

}

////Multiply two matrices, return new matrix C
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
unsigned long int i=0;
unsigned long int j=0;
unsigned long int l=0;
long double sum=0;

for(i=0;i<A->Rows;i+=1){
Entries[i] = malloc(B->Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Entries[%lu} NULL MultiplyMR",i);
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
}


void MultiplyAcrossM(Matrix* A, Matrix*B, char* N){
if(A==NULL || B ==NULL){
printf("\n MultiplyAcross NULL Matrix");
exit(-2);
}

if(A->Rows!=B->Rows || A->Columns!=B->Columns){
printf("\n MultiplyAcrossM rows and columns don't match!");
exit(-1);
}

size_t i=0; 
size_t j=0;
for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns; j+=1){
A->Entries[i][j] = A->Entries[i][j] * B->Entries[i][j];
}
}
A->Name = N;
}


void MultiplyAcrossV(Matrix*A,long double Lr){
if(A==NULL){
printf("\n MultiplyAcross NULL Matrix");
exit(-2);
}

size_t i=0;
size_t j=0;

for(i=0;i<A->Rows;i+=1){

for(j=0;j<A->Columns;j+=1){
A->Entries[i][j]*=Lr;
}

}

}

Matrix* MultiplyAcrossMR(Matrix* A, Matrix*B, char* N){
if(A==NULL || B ==NULL){
printf("\n MultiplyAcross NULL Matrix");
exit(-2);
}

if(A->Rows!=B->Rows || A->Columns!=B->Columns){
printf("\n MultiplyAcrossM rows and columns don't match!");
exit(-1);
}

size_t i=0;
size_t j=0;

Matrix * C = CopyMatrixMR(A,"A Copied");

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns; j+=1){
C->Entries[i][j] = A->Entries[i][j] * B->Entries[i][j];
}
}

C->Name = N;

return C;
}


Matrix* NoBiasMR(Matrix*A){
if(A==NULL){
printf("\n No MAtrix to remove bias");
exit(-2);
}

free(A->Entries[A->Rows-1]);
A->Entries[A->Rows-1]=NULL;
A->Rows-=1;

return A;
}
//Return norm matrix, which are all from Matrix A...
//Essentially it's a copyMatrix
Matrix * NormalizeValuesMR(Matrix*A){
if(A==NULL){
printf("\n No Matrix to Normalize values");
exit(-2);
}
//return CopyMatrixMR(A,"Normalized");
size_t i=0;
size_t j=0;

Matrix* C = CreateMR(CreateE(A->Rows,1),A->Rows,1,"Sum of each row");
long double sum = 0.0;
for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
sum+=A->Entries[i][j];
}
C->Entries[i][0] = sum;
}

return C;
}

////Normalize Matrix given its normalize values
void NormalizeM(Matrix* A, Matrix*Norms,bool Transposed){
if(A==NULL||Norms==NULL){
printf("\n Numm matrices for normalizeM");
exit(-2);
}
if(A->Rows!=Norms->Rows){
printf("\n NormalizeM Rows don't match!");
exit(-2);
}

size_t i=0;
size_t j=0;

if(!Transposed){
for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j]/=Norms->Entries[i][0];
}
}
}
else{
for(i=0;i<A->Columns;i+=1){
for(j=0;j<A->Rows;j+=1){
A->Entries[j][i]/=Norms->Entries[i][0];
}
}
}

}
//


Matrix* AppendBiasM(Matrix*A){
if(A==NULL){
printf("\n Null Matrix Append");
exit(-2);
}
/*
A->Entries = realloc(A->Entries,(A->Rows+1)*sizeof(long double*));
A->Rows+=1;
A->Entries[A->Rows-1] = malloc((A->Columns)*sizeof(long double));
*/

long double ** Entries = CreateE(A->Rows+1,A->Columns);

size_t i=0;
size_t j=0;
for(j=0;j<A->Rows;j+=1){
for(i=0;i<A->Columns;i+=1){
Entries[j][i] = A->Entries[j][i];
}
}

for(i=0;i<A->Columns;i+=1){
Entries[A->Rows][i]=1.0;
}

DeleteEntries(A->Entries,A->Rows);

A->Entries=Entries;
A->Rows+=1;

return A;
}

////Multiply Row by value
void MultiplyRowM(Matrix* M,unsigned long int Row, long double Value){
if(M==NULL){
printf("\n MuitiplyRowM NULL Matrix");
exit(0);
}
if(Row>=M->Rows || Row<0){
printf("\nInvalid Row MultiplyRowM");
exit(0);
}
unsigned long int j=0;
for(j=0;j<M->Columns;j+=1){
M->Entries[Row][j]*=Value;
}
}

void AddRowM(Matrix*M,unsigned long int Column1,unsigned long int Column2, long double Value){
if(M==NULL){
printf("\n Matrix AddRowM NULL");
exit(-1);
}
if(Column1<0 || Column1>=M->Columns || Column2<0||Column2>=M->Columns){
printf("\n AddRowM Columns invalid");
exit(-1);
}
unsigned long int j=0;
for(j=0;j<M->Rows;j+=1){
M->Entries[j][Column2]+=Value*M->Entries[j][Column1];
}
}


long double** CreateE(/*long double**e,*/size_t Rows,size_t Columns){
if(/*e==NULL || */Rows<=0 || Columns<=0){
printf("\nNo entries");
exit(-1);
}

long double** Entries = malloc(Rows*sizeof(long double*));

if(Entries==NULL){
printf("\n Error Creating Entires CreateE");
exit(-1);
}

unsigned long int i=0;
unsigned long int j=0;
for(i=0;i<Rows;i+=1){
Entries[i]=malloc(Columns*sizeof(long double));
if(Entries[i]==NULL){
printf("\n Error Creating Entires CreateE");
exit(-1);
}
for(j=0;j<Columns;j+=1){
Entries[i][j]=0.0;
}
}

return Entries;

}

////Create Matrix given double[][] 2d array, obviously return this
////new matrix
Matrix* CreateMR(long double** E,size_t Rows,size_t Columns,char*Name){
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
void DeleteEntries(long double**E,unsigned long int Rows){
unsigned long int i=0;
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

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j] = 1/(1+expl(-A->Entries[i][j]));
}
}

}

//Relu
void ReluM(Matrix* A){
if(A==NULL){
printf("\n No Matrix to Relu");
exit(0);
}

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
if(A->Entries[i][j]<=0){
A->Entries[i][j]=0.0;
}
}
}

}

//SoftMax
void SoftMaxM(Matrix* A){

if(A==NULL){
printf("\nNo Matrix to SoftMax\n");
exit(-1);
}

unsigned long int i=0;

unsigned long int j=0;

unsigned long int l=0;

long double** ActualM = malloc(A->Rows*sizeof(long double*));

long double sum = 0.0;

for(i =0; i<A->Rows;i+=1){
ActualM[i] = malloc(A->Columns*sizeof(long double));
sum = 0.0;

for(l=0;l<A->Columns;l+=1){

for(j=0; j<A->Rows;j+=1){
sum+=expl(A->Entries[j][l]);
}

if(sum==0.0){
sum  =1.0;
}
ActualM[i][l] = expl(A->Entries[i][l])/sum;

}

}

DeleteEntries(A->Entries,A->Rows);

A->Entries = ActualM;

}

//Mimic DSigmoid
void DSigmoidM(Matrix* A){

if(A==NULL){
printf("\n No Matrix to DSigmoid");
exit(-1);
}

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j]*=(1-A->Entries[i][j]);
}
}

}

//Mimic DRelu
void DReluM(Matrix* A){

if(A==NULL){
printf("\nNo MAtrix to DRelu");
exit(-1);
}

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
if(A->Entries[i][j]>0){
A->Entries[i][j]=1.0;
}
else{
A->Entries[i][j]=0.0;
}
}
}

}

//Mimic DSoftMax
void DSoftMaxM(Matrix*A){

if(A==NULL){
printf("\n No Matrix to DSoftmax");
exit(-1);
}

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
A->Entries[i][j]*=(1-A->Entries[i][j]);
}
}

}

////Print out name of matrix followed by all of its entries
void toString(Matrix* A){
printf("\n%s\n ROWS:%lu COLUMNS:%lu\n",A->Name,A->Rows,A->Columns);
unsigned long int i=0;
unsigned long int j=0;
   for(i=0;i<A->Rows;i+=1){
	for(j=0;j<A->Columns;j+=1){
	   printf("%Lf ",A->Entries[i][j]);
	}
	printf("\n");
   }

}

size_t GetRows(FILE* F,char Delim){

long PrevPosition = ftell(F);

char c;

size_t R = 0;

bool DelimFound=false;

//Scan file until reach either delim before \n or reach \n
while(fscanf(F,"%c",&c)!=EOF){

if(c=='\n'){
if(!DelimFound){
R+=1;
}
else{
DelimFound=false;
}
}
else if(c==Delim){
DelimFound=true;
R+=1;
}

}

fseek(F,PrevPosition,SEEK_SET);

return R;
}

//Iterate until reach new line, this will be column
//MUST DEFINE COLUMN AT THE FIRST ROW AT LEAST!!!!!!!!!!
size_t GetColumns(FILE* F){

long PrevPosition = ftell(F);

//bool NumFound=true;

char c;

size_t C=0;

bool Spaces = false;

while(fscanf(F,"%c",&c)!=EOF){
if(isdigit(c)){
//continue;
//NumFound=true;
C=1;
break;
}
//PrevPosition=ftell(F);
}
//Back to before hit num
//PrevPosition-=1;

//fseek(F,PrevPosition,SEEK_SET);

//unsigned long int C = 0;

bool Dot = false;

//bool Spaces = true;

//char c;

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

if(c==' '){
Spaces=true;
}

if(c=='\n'){
printf("\n Made it to final column:%lu\n",C);
break;
}

}

}
else{
if(Spaces)
C+=1;
Spaces=false;
}

}

//fsetpos(F,PrevPosition);
fseek(F,PrevPosition,SEEK_SET);

return C;

}

//Always return string
// when hit delimiter, return
char* NextString(FILE*F,char D){
if(F==NULL){
return NULL;
}

char* app = malloc(sizeof(char));
app[0]='\0';

//app[1]='\0';
int pos = 0;

char c=' ';

do{

if(fscanf(F,"%c",&c)==EOF){
break;
}

if(c==D){
break;
}
app[pos]=c;
pos+=1;
char* t=realloc(app,(pos+1)*sizeof(char));
if(t==NULL){
printf("\n Error realloc for str");
exit(-1);
}
else{
app=t;
}
app[pos]='\0';
if(app==NULL){
printf("\n Error Getting Next String");
exit(-2);
}
}while(c!=D);


if(strlen(app)==0){
free(app);
app=NULL;
}

return app;

}

//Get Next long double if double, return double, if not return NULL
//If end of file, return -999999999 ld*
//Returns two ld
//first is 0 for a num
//second is 1 for delimiter and a num
//third is 2 for EOF
Ret* NextDouble(FILE*F,char Delimiter){

bool Dot = false;

//long double Num = -999999999;

//R = malloc(sizeof(Ret));
//long double Ret[2];
//unsigned long int Line = 0;
R->Second = -88888888;

size_t ASize = 1;
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
ASize+=1;
char*t=realloc(app,(ASize)*sizeof(char));
if(t==NULL){
printf("\nFailed to realloc for str");
exit(-1);
}
else{
app=t;
}
app[ASize-2] = c;

Dot=true;
}
else if(c==Delimiter){
//Delimiter hit, break away return NULL
//long double D = 0.0;

sscanf(app,"%Lf",&(R->Second));

R->First = 1;
//Ret[1] = D;
free(app);
return R;
}
//else if(c==' '){
//continue;
//}
else{
//if not digit, not., not delimiter
//long double D = 1.0;

sscanf(app,"%Lf",&(R->Second));

R->First = 0;
//Ret[1]=D;
free(app);
return R;
}
}
else{
ASize+=1;
char*t=realloc(app,(ASize)*sizeof(char));
if(t==NULL){
printf("\nFailed to realloc for str");
exit(-1);
}
else{
app=t;
}
app[ASize-2] = c;

}

}

//reached EOF, retu
//long double* LD = malloc(sizeof(long double));

R->First = 2;
R->Second=-999999999;
free(app);
return R;
}

/**
 *Read File, store into matrix
 */
MatrixFileStream* ReadFile(MatrixFileStream* MFS1,char Delimiter){

FILE* F = MFS1->F;

if(F==NULL){
printf("\nUnable to open file:%s",MFS1->FileName);
exit(-4);
}

size_t COLUMNS = GetColumns(F);
size_t ROWS = GetRows(F,Delimiter);

size_t Columns = 0;

size_t Rows = 0;

size_t Size = 1;
//long double ** Entries = malloc(1*sizeof(long double *));
//Entries[0] = malloc((COLUMNS)*sizeof(long double));

//Data** Entries = malloc(sizeof(Data*));

if(ROWS<=0 || COLUMNS<=0){
printf("\n No Rows or Columns");
return NULL;
}

long double Entries[ROWS][COLUMNS];

//Data*Entries=malloc(sizeof(Data));

//Entries[0]=malloc((COLUMNS+1)*sizeof(Data));

while(true){

NextDouble(F,Delimiter);

if(R->First==2||R->First==1){

if(R->First==1){

if(R->Second!=-88888888){
printf("\n RESULT FINAL:%Lf",R->Second);

//(Entries[Rows][Columns]).Entry=R->Second;



//AddEntry(&Entries,R->Second);

Entries[Rows][Columns] = R->Second;


}

}

printf("\n DONE READING");
break;
}

printf("\n CASE: %Lf",R->First);

printf("\n ENTRY: %Lf [%lu,%lu] CASE:%Lf",R->Second,Rows,Columns,R->First);

if(R->Second!=-88888888){
//Columns+=1;
if(Columns>=COLUMNS){
//printf("\nSET COLYMNS TO 0\n");
Columns=0;
Rows+=1;
}
//
if(Rows>=Size){

Size+=1;

/*
Data** t =realloc(Entries,(Rows+1)*sizeof(Data*));
if(t==NULL){
printf("\n Error Reading more rows");
exit(-2);
}
else{
Entries=t;
}
Entries[Rows] = malloc((COLUMNS)*sizeof(Data));
if(Entries[Rows]==NULL){
printf("\n Error Reading more rows");
exit(-2);
}
*/
}
//

//Entries[Rows][Columns].Entry = R->Second;



//AddEntry(&Entries,R->Second);


Entries[Rows][Columns] = R->Second;

//
Columns+=1;
}

}
//Num Rows and Columns to store all values
//
Rows+=1;
printf("\n SIZE:%lu  ROWS:%lu COLUMNS:%lu\n",Size,Rows,COLUMNS);
if(COLUMNS==0){
/*
long long int t=0;
while(t<Rows){
free(Entries[t]);
Entries[t]=NULL;
t+=1;
}
free(Entries);
Entries=NULL;
*/
//DeleteAllEntries(&Entries,Rows*COLUMNS);
return NULL;
}

//free(Entries[Rows]);
//
//

MNew=NULL;

printf("\n MADE IT 4");

//PrintEntries(&Entries,Rows*COLUMNS);

MNew = malloc(sizeof(Matrix));
if(MNew==NULL){
printf("\nFAILED TO Get New Matrix");
exit(-1);
}

MNew->Rows = Rows;
MNew->Columns=COLUMNS;

MNew->Entries=CreateE(Rows,COLUMNS);

if(MNew->Entries==NULL){
        printf("\n Not enough memory for matrix read");
        exit(-1);
}

printf("\n MADE IT 5");
size_t j=0;
size_t k=0;

//Data** E1 = &Entries;
//Data** E2 = NULL;

for(j=0; j<Rows;j+=1){
	/*
	MNew->Entries[j]=malloc((COLUMNS)*sizeof(long double));
	if(MNew->Entries[j]==NULL){
	printf("\n Not enough memory for matrix read");
	exit(-1);
	}
	*/	
        /*
	E2 = E1;	
        if(E2==NULL)
	break;
	*/
	for(k=0; k<COLUMNS;k+=1){
                        //printf("%Lf ",Entries[j][k].Entry);
                        MNew->Entries[j][k]=Entries[j][k];
	
	/*Data* E4 = ((*E2)->Next);
	if(E4==NULL)
	break;
	E2 = &E4;
	*/
	}
        
        //if(Rows!=1 && COLUMNS!=1){

	//E1 = E2;
	/*	
	printf("\n Freeing:%LF",Entries[j][0].Entry); 
	if(Entries[j]!=NULL)
        free(Entries[j]);
	Entries[j]=NULL;                     
        */

  	//}
  	//
  	/*
	Data * E3 = ((*E1)->Next);
 	if(E3==NULL)
	break;
	E1 = &E3;
      	*/
       printf("\n");
}

/*
if(Entries[0]!=NULL)
free(Entries[0]);
*/

/*
//if(Rows!=1)
for(j=1;j<Rows;j+=1)
//for(k=0;k<COLUMNS;k+=1)
free(Entries[j]);
*/

//
//DeleteAllEntries(&Entries,Rows*COLUMNS);

/*
if(Entries!=NULL){
free(Entries);
Entries=NULL;
}
*/
//DeleteData(Data,Rows,COLUMNS);
/*
Matrix* M = malloc(sizeof(Matrix));
M->Rows = Rows;
M->Columns=COLUMNS;
*/
//M->Entries = Entries;

MFS1->F=F;
MFS1->M=MNew;

return MFS1;
}
//fseek(F,PrevPosition,SEEK_SET);
//

void SaveMatrix(Matrix*M,FILE* F){
if(M==NULL){
printf("\n No matrix to Save");
return;
}

/*if(access(FileName,F_OK)!=-1){
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
*/
//FILE* F = fopen(FileName,"w+");
WriteFile(F,M);
//fclose(F);
//}
}

//Writes to file regardless of position
void WriteFile(FILE* F, Matrix* M){

unsigned long int i=0;
unsigned long int j=0;
/*
fprintf(F,"\n%s\n",M->Name);
fprintf(F,"%lu\n",M->Rows);
fprintf(F,"%lu\n",M->Columns);
*/
for(i=0; i<M->Rows;i+=1){
for(j=0; j<M->Columns;j+=1){
fprintf(F,"%Lf",M->Entries[i][j]);
fprintf(F,"%c",' ');
printf("\n STORING:%Lf",M->Entries[i][j]);
}
fprintf(F,"\n");
}

}

//Close file, not delete matrix
void CloseMFS(MatrixFileStream* MFS){
if(MFS!=NULL){
if(MFS->F!=NULL)
fclose(MFS->F);
//if(MFS->M!=NULL)
//free(MFS->M);
//MFS->M=NULL;
free(MFS);
MFS=NULL;
}
}

MatrixFileStream* NewMatrixFileStream(char* Name){
printf("\nStream File:%s\n",Name);
FILE* F = fopen(Name,"r");
if(F==NULL){
printf("\n File Cannot open");
exit(-1);
}

MatrixFileStream* MFS = malloc(sizeof(MatrixFileStream));
MFS->FileName=Name;
MFS->F=F;

return MFS;
}


void RandomizeM(Matrix* A){
if(A==NULL){
printf("\n Matrix is NULL RandomizeM");
exit(-2);
}

unsigned long int i=0;
unsigned long int j=0;

for(i=0;i<A->Rows;i+=1){
for(j=0;j<A->Columns;j+=1){
srandom(random());
A->Entries[i][j] = (random()/(RAND_MAX*1.0));
}
}


}

void NextLine(FILE* F){
char c;
while(fscanf(F,"%c",&c)!=EOF){
if(c=='\n'){
return;
}
}
}

/*
char* Concat(char* s1, char* s2){

char Caty[1+strlen(s1)+strlen(s2)];
strcat(Caty,s1);
strcat(Caty,s2);
Cat = Caty;

return Cat;
}
*/


void AddEntry(Data** E,long double d){
if((*E)==NULL){
*E=malloc(sizeof(Data));
(*E)->Entry = 0.0;
(*E)->Next = NULL;
return;
}

Data** E1 = E;
while((*E1)->Next!=NULL){
Data** E2 = &((*E1)->Next);
E1=E2;
}
(*E1)->Next=malloc(sizeof(Data));
//(*E1)->Next->Entry = 0.0;
Data* E2 = (*E1)->Next;
E2->Entry = d;
E2->Next=NULL;
}

void DeleteAllEntries(Data** E,size_t Len){

Data**E1 = E;

size_t i=0;

while(*E1!=NULL && i<Len){
Data**E2 = &((*E1)->Next);

if(*E1!=NULL)
free(*E1);
*E1=NULL;

E1=E2;

i+=1;
}

free(E);
E=NULL;

}

void PrintEntries(Data**E,size_t Len){

Data ** E2 = E;

size_t i=0;

while(E2!=NULL && i<Len){

//if((*E2)->Entry!=NULL)
printf("\n Data:%LG",(*E2)->Entry);

Data*E3 = (*E2)->Next;
E2=&E3;
i+=1;
}


}

