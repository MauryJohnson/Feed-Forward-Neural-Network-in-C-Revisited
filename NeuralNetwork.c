#include "Layer.c"

typedef struct NN{

//Name of Neural Network
String* Name;

//Determine what type of error to evaluate
//0 is difference,1 is cross entropy
int ErrorType;

//Indicate if error is normalized
bool Normalized;

//Layers of neural network
//STARTS AT INPUT LAYER
Layer** Layers;

}NeuralNetwork;
/*
typedef struct RetCase_{

long double First;
long double Second;

}Ret;
*/
//Append Layer to Neural Network
void AddLayer(NeuralNetwork** N,Layer**L);

//Print entire network
void PrintNetwork(NeuralNetwork*N);

//Create Neural Network, given a network from past or not
NeuralNetwork** CreateNeuralNetwork(Layer* AllLayers);

//Delete NN
void DeleteNetwork(NeuralNetwork**N);

//Save NN
void SaveNetwork(NeuralNetwork**N,char Delim);

//Given filename, parse all layers for neural network
NeuralNetwork** ParseLayers(char* FileName,char Delim);

//Parse integer from user input
int ParseInt();

//Parse double from user input
long double ParseDouble();

Layer** L;
NeuralNetwork**N;


//ARGV[1] CAN BE ARGUMENT FOR FILE
//ARGV[2] CAN BE ARGUMENT FOR DELIMITER
int main(int argc, char**argv){
Layer* AL;

//NeuralNetwork**N=NULL;

if(argc>2){

//DeleteNetwork(ParseLayers(argv[1],argv[2][0]));
N = (ParseLayers(argv[1],argv[2][0]));

//PrintNetwork(N);
//DeleteNetwork(N);
}
else{
N= CreateNeuralNetwork(NULL);
}
//free(N->Name);
//DeleteString(N->Name);
//free(N);


SaveNetwork(N,'_');
/*









*/
PrintNetwork(*N);
DeleteNetwork(N);
//
return 0;
}

//Assume that new layer is already set
void AddLayer(NeuralNetwork**N,Layer**NL){
if(N==NULL){
printf("\n Neural Network is NULL");
exit(-1);
}
if(NL==NULL){
printf("\n New Layer is null");
exit(-1);
}

//Layer * L = N->Layers;
if((*N)->Layers==NULL){
(*N)->Layers = (NL);
Layer** I = (*N)->Layers;
(*I)->Next=NULL;
(*I)->Prev=NULL;
return;
}

Layer**L=(*N)->Layers;

while(((*L)->Next)!=NULL){
Layer** L2=((*L)->Next);
L=L2;
}

(*L)->Next=(NL);
//L->Prev=NULL;
//L->Next->Next=NULL;
//L->Next->Prev=L;
//(*NL)->Prev = L;
}

NeuralNetwork** CreateNeuralNetwork(Layer* AL){
int Layers = -1;
int LayerSize=-1;
int Rows=-1;
int Columns=-1;
int Activation=-1;
//int ActivationFunction=-1;

unsigned long int i=0;
unsigned long int j=0;

NeuralNetwork** N = malloc(sizeof(NeuralNetwork*));

*N=malloc(sizeof(NeuralNetwork));

Layer** Prev;

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

(*N)->ErrorType=Err;

printf("\n Normalized? Enter >0 Yes <=0 No:");

(*N)->Normalized = ParseInt()>0;

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

Layer** IL = NewLayer(NULL,IN,0,0);

(*N)->Layers=IL;

Prev=((*N)->Layers);

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
Columns=(i==1? (*Prev)->Activation->Rows:(*Prev)->Weights->Rows);

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

Layer** H = NewLayer(Prev,Weights,1,Activation);
//Layer**H=&H2;

AddLayer(N,H);

//PrintLayer(H);

Prev=H;

}

}

}

else{
//Iterate all layers parsed from file and just store them into new NN
Layer* L2 = AL;
Layer**L=&L2;
while(L!=NULL){
AddLayer(N,L);

Layer**L2=((*L)->Next);

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
printf("\n\n Neural Network:%s",N->Name!=NULL?N->Name->Name:"NULL");
printf("\n Error type:%d",N->ErrorType);

PrintLayers((*N->Layers));

}

//Parse all layers from file
//use MFS, matrix file stream
NeuralNetwork** ParseLayers(char*FileName,char Delim){

//Read NN file format:
//Parse Name-DELIM-ErrorType-DELIM-Normalized ->Normalized 1 or 0
//IN layer will only have Activation WHETHER ACTIVATED OR NOT
//Hidden layers will have activation WHETHER ACTIVATED OF NOT,
//Weight next, Error whether there or not, 

//Layer* Layers = malloc(sizeof(Layer));

N = malloc(sizeof(NeuralNetwork*));
NeuralNetwork**NN = N;
NN[0]=malloc(sizeof(NeuralNetwork));

(*NN)->Layers=NULL;

MatrixFileStream* MFS = NewMatrixFileStream(FileName);
if(MFS==NULL){
printf("\nNo File Stream Available");
exit(-1);
}

FILE* F = MFS->F;

char* str = NULL;

int i=0;

int p;

do{
str = NextString(F,Delim);
//printf("\n Indicator:%s",str);
if(str!=NULL){
printf("\n Indicator:%s",str);

if(i==0){


(*NN)->Name = Concat(NULL,str);
}
else if(i==1){
p=atoi(str);
if(p<0||p>1)
{
printf("Bad Indicator parsed");
exit(-2);
}
(*NN)->ErrorType=p;
}
else if(i==2){
p=atoi(str);
if(p<0||p>1)
{
printf("Bad Indicator parsed");
exit(-2);
}
(*NN)->Normalized = p==0 ? false:true;
}
free(str);
str=NULL;
}
i+=1;
}while(i<=2);

Layer** Prev = NULL;

i=0;

str = NextString(F,Delim);
free(str);
str=NULL;
str = NextString(F,Delim);
//Get Activation FOR INPUT Layer
ReadFile(MFS,Delim);

Matrix* C = MFS->M;

L = NewLayer(NULL,C,0,0);

AddLayer(NN,L);

Prev=L;

//Get Activation for HIDDEN Layer n
if(str!=NULL)
free(str);
str=NULL;

//Ns,Ns,R,Ns,R,Ns,R,Ns,

while(1){

str=NextString(F,Delim);
if(str==NULL){
break;
}
printf("\nMade it 1");

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
break;
}

printf("\nMade it 2:%s",str);

ReadFile(MFS,Delim);

Matrix* B=MFS->M;

L = NewLayer(Prev,B,1,atoi(str+1));

SetActivation(L,B);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL;
break;
}

printf("\nMade it 3:%s",str);

ReadFile(MFS,Delim);

Matrix* W=MFS->M;
SetWeights(L,W);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL;
break;
}

printf("\nMade it 4:%s",str);

ReadFile(MFS,Delim);

Matrix*E=MFS->M;
SetError(L,E);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL;
break;
}

printf("\nMade it 5:%s",str);

ReadFile(MFS,Delim);

Matrix*GW=MFS->M;
SetGradientWeights(L,GW);

Prev=L;

AddLayer(NN,L);

i+=1;

if(str!=NULL)
free(str);
str=NULL;

}

CloseMFS(MFS);

return NN;
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

scanf("%Lf",&n);

printf("\n%Lf Entered",n);

return n;

}


void SaveNetwork(NeuralNetwork**N,char Delim){
if(N==NULL){
printf("\n No NN to Save");
return;
}
bool Quit = false;
bool Write = false;
long long int i=0;
size_t intSize = 0;
char* Model = NULL;
bool Neg;
do{
Write=false;
Neg=false;
printf("\n Enter Model#:");
i=ParseInt();

printf("\n i:%lld",i);

if(i<=0){
Neg=true;
i*=-1;
}

intSize = (size_t)ceil(log10((i)));
printf("\n Intside:%zu",intSize);

if(Neg || i<=10)
intSize+=1;
if(i==1)
intSize+=1;

Model=malloc((intSize+6)*sizeof(char));
Model[0]='M';
Model[1]='o';
Model[2]='d';
Model[3]='e';
Model[4]='l';
if(Neg)
Model[5]='-';

snprintf(Model+(Neg? 6:5),intSize+6,"%lld",i);

Model[intSize+(Neg?6:5)]='\0';

printf("\n Saving to Model:%s",Model);

if(access(Model,R_OK)==0){
printf("\n File exists... Overwrite  >0 Yes <=0 NO?");
i=ParseInt();
if(i>0){
Write=true;
}
}
else{
Write=true;
}
Quit=true;
//free(Model);
//Model=NULL;
}while(!Quit);

//char* Act = NULL;

char Act[12];

if(Write){
FILE* F = fopen(Model,"w+");
if(F==NULL){
printf("Error Opening model to save");
exit(-1);
}

//NN Name, and information...
fprintf(F,"%s",Model);
//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');
fprintf(F,"%d",(*N)->ErrorType);
//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');
fprintf(F,"%d",((*N)->Normalized? 1:0));
//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

Layer** L = (*N)->Layers;

//Get Previous Most layer
/*
if(L!=NULL)
while((*L)->Prev!=NULL){
Layer**L2 = ((*L)->Prev);
L=L2;
}
*/

intSize = (*L)->ActivationFunction==0? 1:ceil(log10((*L)->ActivationFunction));

if((*L)->ActivationFunction<=10){
intSize+=1;
}

printf("\n IntSize:%zu",intSize);

//Act=malloc((2+intSize)*sizeof(char));
bzero(Act,12);
if(Act==NULL){
printf("\n Error mallocing for activation name");
exit(-1);
}
Act[0]='A';
snprintf(Act+1,2+intSize,"%d",(*L)->ActivationFunction);
//Start from firsy layer on

fprintf(F,"%s","I");

//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

fprintf(F,"%s",Act);

//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

//fprintf(F,"%c",'\n');

//free(Act);
//Act=NULL;

//fclose(F);
SaveMatrix((*L)->Activation,F);

//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

//fprintf(F,"%c",'\n');

Layer**L3=((*L)->Next);
L=L3;

i=0;

while(L!=NULL){

intSize = (*L)->ActivationFunction == 0? 1:ceil(log10((*L)->ActivationFunction));

if((*L)->ActivationFunction<=10){
intSize+=1;
}

bzero(Act,12);

if((*L)->Next==NULL){
fprintf(F,"%s","O");
}
else{
fprintf(F,"%s","H");
//fprintf(F,"%c",'\n');
//fprintf(F,"%c",Delim);
}

//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');


//Act=malloc((2+intSize)*sizeof(char));
Act[0]='A';
snprintf(Act+1,2+intSize,"%d",(*L)->ActivationFunction);
//Start from firsy layer on
//
fprintf(F,"%s",Act);
//
//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');
//fprintf(F,"%c",'\n');

//free(Act);
//Act=NULL;

SaveMatrix((*L)->Activation,F);
bzero(Act,12);
Act[0]='W';


fprintf(F,"%c",Delim);

//fprintf(F,"%s",Act);
fprintf(F,"%c",'\n');
fprintf(F,"%s",Act);

fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

SaveMatrix((*L)->Weights,F);
bzero(Act,12);
Act[0]='E';


fprintf(F,"%c",Delim);

//fprintf(F,"%s",Act);
fprintf(F,"%c",'\n');
fprintf(F,"%s",Act);

fprintf(F,"%c",Delim);
//fprintf(F,"%c",'\n');

SaveMatrix((*L)->Error,F);
bzero(Act,12);
Act[0]='G';
Act[1]='W';

//fprintf(F,"%c",Delim);
fprintf(F,"%c",Delim);
//fprintf(F,"%s",Act);
fprintf(F,"%c",'\n');
fprintf(F,"%s",Act);

fprintf(F,"%c",Delim);
fprintf(F,"%c",'\n');

SaveMatrix((*L)->GradientWeights,F);

//fprintf(F,"%c",'\n');
fprintf(F,"%c",Delim);
//fprintf(F,"%c",'\n');

Layer**L2 = ((*L)->Next);
L=L2;

i+=1;

}



//free(Act);
//Act=NULL;
}

free(Model);
Model=NULL;

}

void DeleteNetwork(NeuralNetwork**N){
if(N==NULL){
printf("\n Delete Network NULL network");
exit(-1);
}

DeleteLayers(((*N)->Layers));

DeleteString((*N)->Name);

free((*N));
*N=NULL;

free(N);
N=NULL;

}
