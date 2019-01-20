#include "Layer.c"

typedef struct NN{

//Name of Neural Network
char* Name;

//Determine what type of error to evaluate
//0 is difference,1 is cross entropy
int ErrorType;

//Indicate if error is normalized
bool Normalized;

//Layers of neural network
//STARTS AT INPUT LAYER
Layer* Layers;

}NeuralNetwork;

//Append Layer to Neural Network
void AddLayer(NeuralNetwork* N,Layer*L);

//Print entire network
void PrintNetwork(NeuralNetwork*N);

//Create Neural Network, given a network from past or not
NeuralNetwork* CreateNeuralNetwork(Layer* AllLayers);

//Delete NN
void DeleteNetwork(NeuralNetwork*N);

//Given filename, parse all layers for neural network
Layer* ParseLayers(char* FileName,char Delim);

//Parse integer from user input
int ParseInt();

//Parse double from user input
long double ParseDouble();


//ARGV[1] CAN BE ARGUMENT FOR FILE
//ARGV[2] CAN BE ARGUMENT FOR DELIMITER
int main(int argc, char**argv){
Layer* AL;
NeuralNetwork*N;
if(argc>2){

AL=ParseLayers(argv[1],argv[2][0]);

//N=

}
else{
N= CreateNeuralNetwork(NULL);
}

PrintNetwork(N);
DeleteNetwork(N);

return 0;
}

//Assume that new layer is already set
void AddLayer(NeuralNetwork*N,Layer*NL){
if(N==NULL){
printf("\n Neural Network is NULL");
exit(-1);
}
if(NL==NULL){
printf("\n New Layer is null");
exit(-1);
}

Layer * L = N->Layers;
if(L==NULL){
L = NL;
L->Next=NULL;
return;
}

while(L->Next!=NULL){
Layer* L2=L->Next;
L=L2;
}

L->Next=NL;
L->Next->Next=NULL;

}

NeuralNetwork* CreateNeuralNetwork(Layer* AL){
int Layers = -1;
int LayerSize=-1;
int Rows=-1;
int Columns=-1;
int Activation=-1;
//int ActivationFunction=-1;

long long int i=0;
long long int j=0;

NeuralNetwork* N = malloc(sizeof(NeuralNetwork));

Layer* Prev;

if(AL==NULL){
printf("\nEnter Number of Layers:");
Layers = ParseInt();
if(Layers<2){
printf("\n Impossible Layer Size");
exit(-1);
}

printf("\nEnter Error Type 0 for difference 1 for cross entropy");
int Err = ParseInt();
if(Err<0||Err>1){
printf("\n Invalid Error type input");
exit(-1);
}

//N=malloc(sizeof(NeuralNetwork));

N->ErrorType=Err;

printf("\n Normalized? Enter >0 Yes <=0 No:");

N->Normalized = ParseInt()>0;

for(i=0;i<Layers;i+=1){
if(i==0){
printf("\nEnter Input Layer Size:");
LayerSize = ParseInt();
if(LayerSize<1){
printf("\n Invalid Layer Size");
exit(-1);
}

Matrix* IN = CreateMR(
CreateE(LayerSize,1),LayerSize,1,"Input");

Layer* IL = NewLayer(NULL,IN,0,0);

N->Layers=IL;

Prev=N->Layers;

//PrintLayers(N->Layers);

}
else if(i>0){
if(i!=Layers-1){
printf("\n Enter Hidden Layer Size:");
}
else{
printf("\nEnter Output Layer Size:");
}
LayerSize = ParseInt();
if(LayerSize<1){
printf("\n Invalid Layer Size");
exit(-1);
}

printf("\nEnter Activation Function type:");

Activation = ParseInt();

if(Activation<0||Activation>3){
printf("\n Invalid Activation Function");
exit(-1);
}

Rows=LayerSize;
Columns=(i==1? Prev->Activation->Rows:Prev->Weights->Rows);

int numsize = ceil(log10(i*1.0));
int size = i==1?(numsize+8):(numsize+7);

printf("\n SIZE:%d",size);

/*
char* num = malloc(size*sizeof(char));

num[0]='W';
num[1]='e';
num[2]='i';
num[3]='g';
num[4]='h';
num[5]='t';
if(numsize==0){
num[6]=1;
numsize=1;
}
num[size-1]='\0';

snprintf(num+6,numsize,"%lld",i);

printf("\n%s",num);
*/

Matrix* Weights = CreateMR(CreateE(Rows,Columns+1),Rows,Columns+1,"");

RandomizeM(Weights);

Layer* H = NewLayer(Prev,Weights,1,Activation);

AddLayer(N,H);

//PrintLayer(H);

Prev=H;

}

}

}

else{
//Iterate all layers parsed from file and just store them into new NN
Layer* L = AL;

while(L!=NULL){
AddLayer(N,L);
Layer*L2=L->Next;
L=L2;
}

}

return N;
}

void PrintNetwork(NeuralNetwork*N){
if(N==NULL){
printf("\n Neural Network is NULL");
exit(-1);
}
printf("\n\n Neural Network:%s",N->Name);
printf("\n Error type:%d",N->ErrorType);

PrintLayers(N->Layers);

}

//Parse all layers from file
//use MFS, matrix file stream
Layer* ParseLayers(char*FileName,char Delim){

//Read NN file format:
//Parse Name-DELIM-ErrorType-DELIM-Normalized ->Normalized 1 or 0
//IN layer will only have Activation WHETHER ACTIVATED OR NOT
//Hidden layers will have activation WHETHER ACTIVATED OF NOT,
//Weight next, Error whether there or not, 

Layer* Layers = malloc(sizeof(Layer));

MatrixFileStream* MFS = NewMatrixFileStream(FileName);
if(MFS==NULL){
printf("\nNo File Stream Available");
exit(-1);
}

FILE* F = MFS->F;

char* str = NULL;

int i=0;

do{
str = NextString(F,Delim);
//printf("\n Indicator:%s",str);
if(str!=NULL){
printf("\n Indicator:%s",str);
free(str);
str=NULL;
}
i+=1;
}while(i<=2);

i=0;

NextString(F,Delim);
NextString(F,Delim);
//Get Activation FOR INPUT Layer
ReadFile(MFS,Delim);

//Get Activation for HIDDEN Layer n

//Ns,Ns,R,Ns,R,Ns,R,Ns,R
//do{

while(i<2){

if(NextString(F,Delim)==NULL){
break;
}
printf("\nMade it 1");
if(NextString(F,Delim)==NULL){
break;
}

printf("\nMade it 2");

ReadFile(MFS,Delim);

if(NextString(F,Delim)==NULL){
break;
}

printf("\nMade it 3");

ReadFile(MFS,Delim);

if(NextString(F,Delim)==NULL){
break;
}

printf("\nMade it 4");

ReadFile(MFS,Delim);

if(NextString(F,Delim)==NULL){
break;
}

printf("\nMade it 5");

ReadFile(MFS,Delim);


i+=1;
//free(str);
//str=NULL;
}
//}while(str[0]!='\0');

CloseMFS(MFS);

return NULL;
}

int ParseInt(){

char *end;
char buf[4096];

int n;

//scanf(" %d",&n);


do {
     if (!fgets(buf, sizeof buf, stdin))
        break;
     // remove \n
   buf[strlen(buf) - 1] = 0;
     //
   n = strtol(buf, &end, 10);
  
   if(n<0){
	printf("\n Error strtol");
	exit(-1);
   }  
 
} while (end != buf + strlen(buf));

printf("\n%d Entered",n);

return n;
}

long double ParseDouble(){

long double n;

/*
do {
     if (!fgets(buf, sizeof buf, stdin))
        break;
     // remove \n
          buf[strlen(buf) - 1] = 0;
     //           //
          if(strtol(buf, &end, 10)<0){
		//printf("\nError parsing double");
	  }
 	 
} while (end != buf + strlen(buf));
     //
*/

scanf("%LG",&n);

printf("\n%LG Entered",n);

return n;

}

void DeleteNetwork(NeuralNetwork*N){
if(N==NULL){
printf("\n Delete Network NULL network");
exit(-1);
}

DeleteLayers(N->Layers);

free(N);
N=NULL;
}
