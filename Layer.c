#include "Matrix.c"


typedef struct Layer_{

//Indicate type of layer
char Type;

//Indicate Activation Function Type
int ActivationFunction;

//Activation Matrix
Matrix* Activation;

//Weight Matrix
Matrix* Weights;

//Error Matrix
Matrix* Error;

//Gradient Weight Matrix
Matrix* GradientWeights;

//Next Layer
struct Layer_** Next;

//Previous Layer
struct Layer_** Prev;

}Layer;
/////////////////////////////////////////////////////////////////////////////////////
//Create New Layer.. IMPORTENT TO KEEP TRACK OF NEXT AND PREV, SET PREV by passing
//Parameter Layer Prev
//Set Next by setting next to Result of NewLaye
Layer **NewLayer(Layer** Prev,Matrix* M,int Type, int ActivationType);

//Add new layer
//void AddLayer(Layer*Layers,Layer*NewL);

//Delete all layers of NN;
void DeleteLayers(Layer** Head);

//Print ALL Layers Starting from begin
void PrintLayers(Layer* L);

//Print A Layer
void PrintLayer(Layer*L);
/////////////////////////////////////////////////////////////////////////////////////
/*
int main(int argc, char** argv){


MatrixFileStream* MFS1 = NewMatrixFileStream("M1");
MatrixFileStream* MFS2 = NewMatrixFileStream("M2");//malloc(sizeof(MatrixFileStream));

Layer* L = malloc(sizeof(Layer));

ReadFile(MFS1,'_');
L->Weights = MFS1->M;

L->Next=malloc(sizeof(Layer));
L->Next->Prev=L;

ReadFile(MFS2,'_');
L->Next->Weights = MFS2->M;

//L->Next->Next=malloc(sizeof(Layer));

L->Prev=malloc(sizeof(Layer));

//CloseMFS(MFS1);

ReadFile(MFS1,'_');
L->Prev->Weights = MFS1->M;
L->Prev->Next=L;

//L->Prev->Prev=malloc(sizeof(Layer));

PrintLayers(L);

DeleteLayers(L);

CloseMFS(MFS1);
CloseMFS(MFS2);

return 0;
}
*/

//Print One Layer from neural net
void PrintLayer(Layer* L){

printf("\n LAYER TYPE:%c LAYER ACTIVATION TYPE:%d",L->Type,L->ActivationFunction);
Matrix* M = L->Activation;
if(M!=NULL)
toString(M);
M = L->Weights;
if(M!=NULL)
toString(M);
M=L->Error;
if(M!=NULL)
toString(M);
M=L->GradientWeights;
if(M!=NULL)
toString(M);

}

//Print Layer Starting From All the way Previous to All the way END
void PrintLayers(Layer*L){
if(L==NULL){
printf("\n No Layers");
return;
}

Layer**P = NULL;

if(L->Prev!=NULL){
P=(L->Prev);
while((*P)->Prev!=NULL){
printf("\nGOING TO PREV");
Layer** P2 = (*P)->Prev;
P=P2;
}
}
else{
P=&L;
}

unsigned long int i=0;
while(P!=NULL){
printf("\nPrint Layer:%lu",i);
PrintLayer(*P);
Layer**P2=(*P)->Next;
P=P2;
i+=1;
}

}

/*
void AddLayer(Layer*Layers,Layer*NewL){
if(Layers==NULL){
Layers = NewL;
}
else{
Layer* L2 = Layers;

while(L2!=NULL){
Layer* L3=L2->Next;
L2=L3;
}

L2=NewL;

}
}
*/

//Create a new valid layer for neural net
Layer ** NewLayer(Layer** Prev,Matrix* M,int Type, int ActivationType){

Layer** L =malloc(sizeof(Layer*));
L[0]=malloc(sizeof(Layer));

if(M==NULL){
printf("\n FAILURE GETTING MATRIX");
exit(-3);
}

if(L==NULL){
printf("\n FAILURE Error creating new layer!");
exit(-4);
}

switch(Type){
case 0:
	(*L)->Activation = M;
	(*L)->Type='I';
	break;
case 1:
	(*L)->Weights=M;
	(*L)->Type = 'H';
	break;
case 2:
	(*L)->Activation=M;
	(*L)->Type = 'O';
	break;
default:
	printf("\n Error! Invalid Entries for New Layer!");
	exit(-3);
}

if(ActivationType>3 || ActivationType<0){
printf("\nNo Activation Function Specified");
exit(-3);
}

(*L)->ActivationFunction=ActivationType;

//Previous layer created
(*L)->Prev = Prev==NULL? NULL:Prev;

//Brand ney layer
(*L)->Next = NULL;

return L;
}

//Delete ALL Layers... Start By Deleting ALL Prev and Next Layers along with their
//Matrices
//Then at end delete curr layer AND All of its Matrices
void DeleteLayers(Layer** L){
if(L==NULL){
printf("\n Layer already deleted");
return;
}

Layer**P=(*L)->Prev;
Layer**N=(*L)->Next;
Matrix* M = NULL;
while(P!=NULL && N!=NULL){
if(P!=NULL){

printf("\n Deleting:");
PrintLayer(*P);

//M=P->Activation;
if((*P)->Activation!=NULL)
DeleteMatrixM((*P)->Activation);

//M=P->Weights;
if((*P)->Weights!=NULL)
DeleteMatrixM((*P)->Weights);

//M=P->Error;
if((*P)->Error!=NULL)
DeleteMatrixM((*P)->Error);

//M=P->GradientWeights;
if((*P)->GradientWeights!=NULL)
DeleteMatrixM((*P)->GradientWeights);

Layer** P2=(*P)->Prev;

free(*P);
*P=NULL;
free(P);
P=NULL;
P=P2;
}

if(N!=NULL){

printf("\n\n Deleting:\n\n");
PrintLayer(*N);

//M=N->Activation;
if((*N)->Activation!=NULL)
DeleteMatrixM((*N)->Activation);

//M=N->Weights;
if((*N)->Weights!=NULL)
DeleteMatrixM((*N)->Weights);

//M=N->Error;
if((*N)->Error!=NULL)
DeleteMatrixM((*N)->Error);

//M=N->GradientWeights;
if((*N)->GradientWeights!=NULL)
DeleteMatrixM((*N)->GradientWeights);

Layer** N2 = (*N)->Next;
//free(&N);
free(*N);
*N=NULL;
free(N);
N=NULL;
N=N2;
}

}

if((*L)!=NULL){
//M=L->Activation;
if((*L)->Activation!=NULL)
DeleteMatrixM((*L)->Activation);

//M=L->Weights;
if((*L)->Weights!=NULL)
DeleteMatrixM((*L)->Weights);

//M=L->Error;
if((*L)->Error!=NULL)
DeleteMatrixM((*L)->Error);

//M=L->GradientWeights;
if((*L)->GradientWeights!=NULL)
DeleteMatrixM((*L)->GradientWeights);

free((*L));
(*L)=NULL;

free(L);
L=NULL;

}

}

void SetGradientWeights(Layer** L, Matrix*GW){
if(L==NULL){
printf("Layer is NULL! FAILURE TO SET");
exit(-4);
}
if((*L)->GradientWeights!=NULL){
DeleteMatrixM((*L)->GradientWeights);
}
(*L)->GradientWeights=GW;
}

void SetWeights(Layer** L,Matrix* W){
if(L==NULL){
printf("Layer is NULL! FAILURE TO SET");
exit(-4);
}

if((*L)->Weights!=NULL)
DeleteMatrixM((*L)->Weights);
(*L)->Weights=W;
}

Matrix* GetWeights(Layer*L){
if(L==NULL){
printf("Layer is NULL! FAILURE TO GET");
exit(-4);
}

return L->Weights;
}

void SetActivation(Layer**L,Matrix* A){
if(L==NULL){
printf("Layer is NULL! FAILURE TO SET");
exit(-4);
}
if((*L)->Activation!=NULL)
DeleteMatrixM((*L)->Activation);
(*L)->Activation=A;
}

Matrix* GetActivation(Layer*L){
if(L==NULL){
printf("Layer is NULL! FAILURE TO GET");
exit(-4);
}

return L->Activation;
}

void SetError(Layer**L,Matrix*E){
if(L==NULL){
printf("Layer is NULL! FAILURE TO SET");
exit(-4);
}
if((*L)->Error!=NULL){
DeleteMatrixM((*L)->Error);
}
(*L)->Error=E;
}

Matrix* GetError(Layer*L){
if(L==NULL){
printf("Layer is NULL! FAILURE TO GET");
exit(-4);
}
return L->Error;
}

/**
 *Perform Activation Type Function on layer's activation matrix
 */
void Activate(Layer*L){
switch(L->ActivationFunction){
case 1:
	SigmoidM(L->Activation);
	break;
case 2:
	ReluM(L->Activation);
	break;
case 3:
	SoftMaxM(L->Activation);
	break;
default:
	printf("\n No Activation function Specified!!");
	exit(-4);
}
}

/*
void PrintLayer(Layer*L){
}
*/

