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

//Assess the error and then propogate that error back
int BackPropagate(NeuralNetwork** NN, Matrix*Error,bool Normalized);

//Computer gradient descent given error type and error values
int Gradient(NeuralNetwork**NN,long double lr);

//add all gradients to weights
int Learn(NeuralNetwork**NN);

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

Layer** NewL;

//Matrix* MNew=NULL;

//MatrixFileStream*MFS = NULL;
//ARGV[1] CAN BE ARGUMENT FOR FILE
//ARGV[2] CAN BE ARGUMENT FOR DELIMITER
int main(int argc, char**argv){
Layer* AL;
char Delim = '+';

NeuralNetwork**N = NULL;

//Use Existing Neural Network or Create one
if(argc>3 && (argc>3? strlen(argv[0])!=0:false)){

N = (ParseLayers(argv[1],argv[argc-1][0]));

}
else{

Delim = (argc>2? (strlen(argv[argc-1])>0?argv[argc-1][0]:'+'):'+');
N = CreateNeuralNetwork(NULL);

}
//printf("\n Enter training data file:");

//SaveNetwork(N,Delim);

//Used to parse matrices from file
MatrixFileStream* MFS;

long double Lr = 0.0;

char* TrainFile = NULL;

//Check if created new matrix or used existing
if(argc>3){
//int idx2 = argc-2;
if(argc>4){
if(sscanf(argv[argc-1],"%LF",&Lr)<0){
printf("\n Bad Learning Rate Parsed");
Lr = -1;
}
}
//else{
Delim = argv[argc-1][0];
//}
//MFS = NewMatrixFileStream(argv[2]);
TrainFile = argv[2];
}
else{
int idx = -1;

if(argc>3){
if(sscanf(argv[argc-2],"%LF",&Lr)<0){
printf("\n Bad Learning Rate Parsed");
Lr = -1;
}
}

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
//snprintf(argv[argc-2],strlen(argv[argc-2]),"%LF",Lr);
}

//printf("Enter training data file/folder:");
//char FIN[255];
//scanf("%s",FI);

if(idx!=-1)
//MFS = NewMatrixFileStream(argv[1]);
TrainFile=argv[1];
}

//Train neural network using Matrix File Stream

int err = -1;

//long double lr;

//printf("\nEnter Learning Rate:");

//SaveNetwork(N,Delim);

Lr = 0.01;

//scanf("%LF",&Lr);
//scanf("%c");

//long double correct = 0;

int correct = 0;

int test = 0;

if(Lr>0){

long long int iteration = 0;

bool AllCorrect = false;

for(iteration=0;iteration<100;iteration+=1){

AllCorrect=true;

correct = 0;

test = 0;

MFS = NewMatrixFileStream(TrainFile);

while(ReadFile(MFS,Delim)!=NULL){

//Feed
err = FeedForward(N,MFS->M);

//exit(-1);

DeleteMatrixM(MFS->M);

printf("\n\n\n MADE IT");
MatrixFileStream* MFS2 = ReadFile(MFS,Delim);
printf("\n\n\n MADE IT");

if(MFS2!=NULL){

if(MFS!=NULL){
//Back Propagate error
printf("\n Made 1");
err = BackPropagate(N,CopyMatrixMR(MFS->M,"MNew Copy"),(*N)->Normalized==1);
}

if(err==1){
correct+=1;
//break;
}

test+=1;


if((double)correct / (double)(test)==1.0){
//AllCorrect = true;
}
else{
AllCorrect=false;
}

DeleteMatrixM(MFS2->M);

//CloseMFS(MFS2);

}

else{
printf("\n Network BackPropogate couldn't read more info");
break;
}


if(err!=1){

Gradient(N,Lr);

Learn(N);

}

}

printf("\n Percent Correct: %f Amount Correct:%d",(double)correct/(double)(test),correct);

CloseMFS(MFS);

if(AllCorrect){
break;
}

//DeleteMatrixM(MFS->M);

}

}
else{
printf("\n Learning rate must be greater than 0!");
//CloseMFS(MFS);
}

SaveNetwork(N,Delim);

/*





*/

//CloseMFS(MFS);
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

Layer**H=NULL;

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

IN->Entries[LayerSize-1][0] = 1.0;

Layer**IL = NULL;
Layer*** IL2 = NULL;
IL2 = NewLayer(NULL,IN,0,0);

IL = *IL2;

(*N)->Layers=IL;

Prev=(IL);

//PrintLayers(N->Layers);

}
else if(i>0){
if(i!=Layers-1){
printf("\n Enter Hidden Layer Size:");
}
else{
printf("\nEnter Output Layer Size:");
}
LayerSize = ParseInt() + (i==Layers-1? 0:2);
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
Weights = CreateMR(CreateE(i==Layers-1? Rows:Rows-1,Columns),i==Layers-1? Rows:Rows-1,Columns,"Weights");

Matrix* GradientWeights = NULL;
GradientWeights = CreateMR(CreateE(i==Layers-1? Rows:Rows-1,Columns),i==Layers-1? Rows:Rows-1,Columns,"GradientWeights");

Matrix* Error = NULL;

Matrix* ActivationM=  NULL;
ActivationM = CreateMR(CreateE(Rows,(*Prev)->Activation->Columns),Rows,(*Prev)->Activation->Columns,"Activation");

if(i!=Layers-1)
ActivationM->Entries[Rows-1][0] = 1.0;

Error = CreateMR(CreateE(Rows,(*Prev)->Activation->Columns),Rows,(*Prev)->Activation->Columns,"Error");

RandomizeM(Weights);

//Layer** H = NULL;
Layer*** H2 = NULL;

H2 = NewLayer(Prev,Weights,1,Activation);

H = *H2;

(*H)->Activation = ActivationM;

(*H)->GradientWeights=GradientWeights;

(*H)->Error =Error;

AddLayer(N,H);

//free(H);

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

PrintLayers(*((*N)->Layers));

return N;
}


int FeedForward(NeuralNetwork** NN, Matrix* Input){

if(NN==NULL){
printf("\n Neural Network does not exist");
exit(-2);
}

if(Input==NULL){
printf("\n Input does not exist");
exit(-2);
}

if(Input->Rows!=(*((*NN)->Layers))->Activation->Rows-1){
printf("\n Input rows:%lu does not match activation rows:%lu",Input->Rows,(*((*NN)->Layers))->Activation->Rows);
exit(-2);
}

size_t ii = 0;

for(ii=0;ii<Input->Rows;ii+=1){

(*((*NN)->Layers))->Activation->Entries[ii][0] = Input->Entries[ii][0];

}

Layer** L =NULL; 
Layer** L2=NULL;

for(L = (*((*NN)->Layers))->Next; L!=NULL; L2=((*L)->Next),L=L2){

if((*L)->Activation!=NULL)

DeleteMatrixM((*L)->Activation);


if((*L)->Next!=NULL)

(*L)->Activation = AppendBiasM(MultiplyMR((*L)->Weights,(*(*L)->Prev)->Activation,"WXA"));

else

(*L)->Activation = (MultiplyMR((*L)->Weights,(*(*L)->Prev)->Activation,"WXA"));

Activate(*L);

}

printf("\n Finished Feeding Forward:\n");

PrintLayers((*(*NN)->Layers));

return 0;
}

int BackPropagate(NeuralNetwork** NN, Matrix*Error,bool Normalized){
if(NN==NULL){
printf("\n No NN to back propoget");
exit(-2);
}
if(Error==NULL){
printf("\n No Error given");
exit(-2);
}

Layer** L = (*NN)->Layers;
while((*L)->Next!=NULL){
Layer** L2 = ((*L)->Next);
L=L2;
}

bool NoError=true;

if((*L)->Activation->Rows!=Error->Rows){
printf("\n Backpropogation error rows don't match activation rows");
exit(-2);
}

size_t i=0;
for(i=0;i<Error->Rows && i<(*L)->Activation->Rows;i+=1){
printf("\n Entering expected output:%LF - %LF ==",Error->Entries[i][0],(*L)->Activation->Entries[i][0]);

Error->Entries[i][0] = Error->Entries[i][0] - (*L)->Activation->Entries[i][0];

printf("%LF\n",Error->Entries[i][0]);

}

printf("\n Made it 0");

long double e = 0.000;

for(i=0; i<Error->Rows && i<(*L)->Activation->Rows;i+=1){

e = (Error->Entries[i][0] <0? Error->Entries[i][0]*-1:Error->Entries[i][0]);

if(!(e<0.001)){
printf("\n Still error for entry: %lu",i+1);
NoError=false;
}

}

if(NoError){
printf("\n No error found");
DeleteMatrixM(Error);
return 1;
}

printf("\n Made it 0.5");

DeleteMatrixM((*L)->Error);

(*L)->Error = Error;
Layer** L2 = NULL;

for(L=L;L!=NULL;L2 = (*L)->Prev,L=L2){
if(L==NULL){
break;
}
if((*L)->Prev==NULL){
break;
}
if((*(*L)->Prev)->Prev==NULL){
break;
}
Matrix*Normalized=NULL;

if(Normalized){
Normalized = NormalizeValuesMR((*L)->Weights); 
//NormalizeM(WeightsTransposed,Normalized);
}

Matrix* WeightsTransposed = TransposeMR((*L)->Weights,"WT");

if(Normalized){
NormalizeM(WeightsTransposed,Normalized,true);
DeleteMatrixM(Normalized);
}

printf("\n\n\n\n\n Made it 1");
Matrix* WTXE = MultiplyMR(WeightsTransposed,(*L)->Activation,"WTXE");

DeleteMatrixM(WeightsTransposed);

/*
DeleteMatrixM(
(*(*L)->Prev)->Error); 
*/

DeleteMatrixM((*(*L)->Prev)->Error);

(*(*L)->Prev)->Error = WTXE;

printf("\n Made it 2");

}

PrintNetwork(*NN);

printf("\n Made it 3");
return 0;
}


int Gradient(NeuralNetwork**NN, long double Lr){
if(NN==NULL){
printf("\n No neural network to perform gradient descent");
exit(-3);
}

Layer**L = (*((*NN)->Layers))->Next;
Layer** L2 = NULL;

for(L = (*((*NN)->Layers))->Next;L!=NULL;L2=(*L)->Next,L=L2){

Matrix* GradientWeights = NULL;
Matrix* ActivationTranspose = NULL;
ActivationTranspose = TransposeMR((*((*L)->Prev))->Activation,"Activation Transpose");

switch((*L)->ActivationFunction){

case 0:
    printf("\n Using no Derivative, Randomizing Weights");
        
    RandomizeM((*L)->Activation);
    break;
case 1:
    printf("\n Using Derivative of Sigmoid");
    
    DSigmoidM((*L)->Activation);   
    break;
case 2:
    printf("\n Using Derivative of ReLu");
    
    DReluM((*L)->Activation);
    break;
case 3:
    printf("\n Using Derivative of SoftMax");

    DSoftMaxM((*L)->Activation);
    break;
default:
    printf("\n Error! No Activation Function Specified!");
    exit(-2);
}
    MultiplyAcrossV((*L)->Activation,Lr);
    MultiplyAcrossM((*L)->Activation,(*L)->Error,"AXE");

    if((*L)->Next!=NULL)
    NoBiasMR((*L)->Activation);
 
    DeleteMatrixM((*L)->GradientWeights);

    (*L)->GradientWeights =  MultiplyMR(((*L)->Activation),ActivationTranspose,"(d/dA(A)*E*Lr)xA^T");

    DeleteMatrixM(ActivationTranspose);

    //(*L)->GradientWeights = GradientWeights;
}


return 0;
}


int Learn(NeuralNetwork**NN){
if(NN==NULL){
printf("\n No Neural Network to learn");
exit(-2);
}

Layer** L = (*((*NN)->Layers))->Next;
Layer**L2 = NULL;

for(L = (*((*NN)->Layers))->Next;L!=NULL;L2=(*L)->Next,L=L2){

AddM((*L)->Weights,(*L)->GradientWeights,1.0,"W + GW");

}

return 0;

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

Layer***L4 = NULL;

L4= NewLayer(NULL,C,0,0);

Layer** L = *L4;

AddLayer(NN,L);

Prev=L;

//Get Activation for HIDDEN Layer n
if(str!=NULL)
free(str);
str=NULL;

//Ns,Ns,R,Ns,R,Ns,R,Ns,

//int Activation;

char str2[10];

Layer** L2 = NULL;

while(1){

str=NextString(F,Delim);
if(str==NULL){
printf("\n Break 1");
break;
}
printf("\nMade it 1");

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
printf("\n Break 2");
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

//L
//Layer** L2 = NULL;

Layer***L3 = NULL;

L3 = NewLayer(Prev,B,1,atoi(str2));

L2=*L3;

SetActivation(L2,B);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL;
printf("\n Break 3");
break;
}

printf("\nMade it 3:%s",str);

ReadFile(MFS,Delim);

Matrix* W=MFS->M;
SetWeights(L2,W);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL;
//printf("\n Break 1");
//
printf("\n Break 4");
break;
}

printf("\nMade it 4:%s",str);

ReadFile(MFS,Delim);

Matrix*E=MFS->M;
SetError(L2,E);

free(str);
str=NULL;
str=NextString(F,Delim);
if(str==NULL){
//DeleteLayers(L);
//free(L);
//L=NULL
printf("\n Break 5");
break;
}

printf("\nMade it 5:%s",str);

ReadFile(MFS,Delim);

Matrix*GW=MFS->M;
SetGradientWeights(L2,GW);

Prev=L2;

AddLayer(NN,L2);

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

//Create a new valid layer for neural net
Layer *** NewLayer(Layer** Prev,Matrix* M,int Type, int ActivationType){
//
NewL =malloc(sizeof(Layer*));

if(NewL==NULL){
printf("\n Failure mallocing for new  layer");
exit(-2);
}
//
NewL[0]=malloc(sizeof(Layer));
if(NewL[0]==NULL){
printf("\n Failure mallocing for new  layer");
exit(-2);
}
//
//
if(M==NULL){
printf("\n FAILURE GETTING MATRIX");
exit(-3);
}
//
if(NewL==NULL){
printf("\n FAILURE Error creating new layer!");
exit(-4);
}
//

switch(Type){
case 0:
        (NewL[0])->Activation = M;
        (NewL[0])->Type='I';
        break;
case 1:
        (NewL[0])->Weights=M;
        (NewL[0])->Type = 'H';
        break;
case 2:
        (NewL[0])->Activation=M;
        (NewL[0])->Type = 'O';
        break;
default:
        printf("\n Error! Invalid Entries for New Layer!");
        exit(-3);
}

if(ActivationType>3 || ActivationType<0){
printf("\nNo Activation Function Specified");
exit(-3);
}

(*NewL)->ActivationFunction=ActivationType;

//Previous layer created
(*NewL)->Prev = Prev;
//
////Brand ney layer
(*NewL)->Next = NULL;
//
return &NewL;
}
//
