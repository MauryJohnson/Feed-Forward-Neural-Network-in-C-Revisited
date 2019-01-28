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

//Feed Data Forward into network
//Return status
int FeedForward(NeuralNetwork** NN, Matrix* Input);

//Delete NN
void DeleteNetwork(NeuralNetwork**N);

//Save NN
void SaveNetwork(NeuralNetwork**N,char D);

//Given filename, parse all layers for neural network
NeuralNetwork** ParseLayers(char* FileName,char Delim);

//Parse integer from user input
int ParseInt();

//Parse String followed by a breaking character
char* ParseString();

//Parse double from user input
long double ParseDouble();

//Clear Stdin buffer
void ClearBuffer();

//Points to a pointer of a layer
//Layer** L;

//Points to a pointer to a neural network
//NeuralNetwork**N;

//ARGV[1] CAN BE ARGUMENT FOR FILE
//ARGV[2] CAN BE ARGUMENT FOR DELIMITER
int main(int argc, char**argv){
Layer* AL;
char Delim = '+';

NeuralNetwork**N = NULL;

//Use Existing Neural Network or Create one
if(argc>3 && (argc>3? strlen(argv[0])!=0:false)){

N = (ParseLayers(argv[1],argv[3][0]));

}
else{

Delim = (argc>2? (strlen(argv[2])>0?argv[2][0]:'+'):'+');
N = CreateNeuralNetwork(NULL);

}
//printf("\n Enter training data file:");

//SaveNetwork(N,Delim);

//Used to parse matrices from file
MatrixFileStream* MFS;

//Check if created new matrix or used existing
if(argc>3){
//int idx2 = argc-2;
/*
if(argc!=4){
printf("\n Delimiter UNDEFINED!");
idx2 = argc-1;
}
*/
//else{
Delim = argv[argc-1][0];
//}
MFS = NewMatrixFileStream(argv[argc-2]);
}
else{
int idx = -1;
if(argc<3){
if(argc<2){
printf("\n Training Data UNDEFINED!\n");
}
printf("\n Delimiter UNDEFINED!\n");
idx = 1;
}
else{
idx = 1;
Delim = argv[argc-1][0];
}

//printf("Enter training data file/folder:");
//char FIN[255];
//scanf("%s",FI);

if(idx!=-1)
MFS = NewMatrixFileStream(argv[idx]);
}

//Train neural network using Matrix File Stream

while(ReadFile(MFS,Delim)!=NULL){

DeleteMatrixM(MFS->M);

}







SaveNetwork(N,Delim);

/*







*/

CloseMFS(MFS);
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
size_t LayerSize=-1;
size_t Rows=-1;
size_t Columns=-1;
int Activation=-1;
//int ActivationFunction=-1;

unsigned long int i=0;
unsigned long int j=0;

NeuralNetwork** N = NULL;
N = malloc(sizeof(NeuralNetwork*));

N[0] = NULL;
NeuralNetwork* N2 = NULL;
N2 = malloc(sizeof(NeuralNetwork));
N[0]=N2;
N[0]->Layers = NULL;

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

LayerSize = ((size_t)ParseInt())+1;

if(LayerSize<1){
printf("\n Invalid Layer Size");
exit(-1);
}

Matrix* IN = NULL;

IN = CreateMR(CreateE(LayerSize,1),LayerSize,1,"Input");

Layer**IL = NULL;
IL = NewLayer(NULL,IN,0,0);

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
LayerSize = ParseInt() + (i==Layers-1? 0:1);
if(LayerSize<1){
printf("\n Invalid Layer Size");
exit(-1);
}

printf("\nEnter Activation Function type 0 none 1 Sigmoid 2 Relu 3 SoftMax:");

Activation = ParseInt();

if(Activation<0||Activation>3){
printf("\n Invalid Activation Function");
exit(-1);
}

Rows=LayerSize;
Columns=(size_t)(*Prev)->Activation->Rows;

int numsize = ceil(log10(i*1.0));
int size = i==1?(numsize+8):(numsize+7);

printf("\n SIZE:%d",size);

Matrix* Weights = NULL;
Weights = CreateMR(CreateE(Rows,Columns),Rows,Columns,"Weights");

Matrix* ActivationM=  NULL;
ActivationM = CreateMR(CreateE(Rows,(*Prev)->Activation->Columns),Rows,(*Prev)->Activation->Columns,"Activation");

RandomizeM(Weights);

Layer** H = NULL;

H = NewLayer(Prev,Weights,1,Activation);

(*H)->Activation = ActivationM;

AddLayer(N,H);

//(*Prev)->Next = H;

//(*Prev)->Next = H;

//PrintLayer(H);

Prev=H;

//DeleteLayers(H);

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

NeuralNetwork** N = malloc(sizeof(NeuralNetwork*));
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

Layer ** L = NewLayer(NULL,C,0,0);

AddLayer(NN,L);

Prev=L;

//Get Activation for HIDDEN Layer n
if(str!=NULL)
free(str);
str=NULL;

//Ns,Ns,R,Ns,R,Ns,R,Ns,

//int Activation;

char str2[10];

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

bzero(str2,10);
int h=1;
int sz = 0;
for(h=0;h<9 && h<strlen(str);h+=1){
if(isdigit(str[h])){
printf("\n IS DIGIT \n");
str2[sz]=str[h];
sz+=1;
}
}
//snprintf(str2,9,"%s",str);

//Activation = atoi(str2);

printf("\n Activation:%s",str2);

ReadFile(MFS,Delim);

Matrix* B=MFS->M;

L = NewLayer(Prev,B,1,atoi(str2));

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


char* ParseString(){
char* end;
char buf[4086];
//int n;

do {
     if (!fgets(buf, sizeof buf, stdin))
        break;
     // remove \n
         buf[strlen(buf) - 1] = 0;
              //
                 strtol(buf, &end, 4096);
     
                  /*  if(n<0){
                            printf("\n Error strtol");
                                    exit(-1);
                                       }
     */
                                       } while (end != buf + strlen(buf));
     


//void ClearBuffer();
                                       //printf("\n%d Entered",n);
  	ClearBuffer();   
                                       return end;

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

ClearBuffer();

printf("\n%Lf Entered",n);

return n;

}


void ClearBuffer(){

while(getchar()!='\n');

}

void SaveNetwork(NeuralNetwork**N,char Delim){
if(N==NULL){
printf("\n No NN to Save");
return;
}

//char Delim = '+';

/*
printf("\n Enter Delimiter:");
char Delims[10];
fscanf(stdin,"%c",Delims);
Delim = Delims[0];
*/
//char Delims[10];
//scanf("%s",Delims);

/*
if(strlen(Delims)>1){
printf("\n Error parsing delimiter");
exit(-1);
}
if(strlen(Delims)>0)
Delim = Delims[0];
*/

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
fprintf(F,"%c",'\n');

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

fclose(F);

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

NeuralNetwork* N2 = (N[0]);
//free((*N));
//*N=NULL;

free(N);
N=NULL;

free(N2);
N2=NULL;


}
