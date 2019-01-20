#include "Layer.c"

typedef struct NN{

//Name of Neural Network
char* Name;

//Determine what type of error to evaluate
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
void CreateNeuralNetwork(Layer* AllLayers);

//Given filename, parse all layers for neural network
Layer* ParseLayers(char* FileName);

//Parse integer from user input
int ParseInt();

//Parse double from user input
long double ParseDouble();

int main(int argc, char**argv){
//printf("Enter Num:");
//ParseInt();
//ParseDouble();
CreateNeuralNetwork(NULL);



return 0;
}

//Assume that new layer is already set
void AddLayer(NeuralNetwork*N,Layer*NL){
if(NL==NULL){
printf("\n New Layer is null");
exit(-1);
}

Layer * L = N->Layers;
Layer* P = NULL;

while(L!=NULL){
Layer* L2=L->Next;
L=L2;
P=L->Prev;
}

L = NL;
L->Next=NULL;
L->Prev=P;

}

void CreateNeuralNetwork(Layer* AL){
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

N=malloc(sizeof(NeuralNetwork));

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

AddLayer(N,NewLayer(NULL,IN,0,0));

Prev=N->Layers;

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

printf("\nEnter Activation Function type");
Activation = ParseInt();
if(Activation<0||Activation>3){
printf("\n Invalid Activation Function");
exit(-1);
}

Rows=LayerSize;
Columns=(i==1? Prev->Activation->Rows:Prev->Weights->Rows);

char* num = malloc(ceil(log10(i*1.0)+6)*sizeof(char));

num[0]='W';
num[1]='e';
num[2]='i';
num[3]='g';
num[4]='h';
num[5]='t';

sprintf(num,"%lld",i);

printf("\n%s",num);

Matrix* Weights = CreateMR(CreateE(Rows,Columns+1),Rows,Columns+1,num);

RandomizeM(Weights);

Layer* H = NewLayer(Prev,Weights,1,Activation);

AddLayer(N,H);

Prev=H;

}

}

}

else{



}

void PrintNetwork(NeuralNetwork*N){
if(N==NULL){
printf("\n Neural Network is NULL");
exit(-1);
}
printf("\n Neural Network:%s",N->Name);
printf("\n Error type:%d",N->ErrorType);

PrintLayers(N->Layers);

}

Layer* ParseLayers(char*FileName){


return NULL;
}

int ParseInt(){

char *end;
char buf[4096];

int n;

do {
     if (!fgets(buf, sizeof buf, stdin))
        break;

     // remove \n
     buf[strlen(buf) - 1] = 0;
     //
   n = strtol(buf, &end, 10);
   
} while (end != buf + strlen(buf));

sprintf(end,"%d",n);

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
