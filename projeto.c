#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define true 1
#define false 0

typedef struct pouso{
    char codigoDeVooA[7];
    char tipoDeVooA[2];
    int combustivel;
} Pouso;

//lista de pouso
typedef struct listaPouso{
	void *pouso;	
	struct listaPouso *prox;
} ListaPouso;

// cabeçalho de pouso
typedef struct headerA{
	ListaPouso *headA; //ponteiro p o primero elemento da lista
	ListaPouso *tailA; //ponteiro p o ultimo elemento da lista
    int qntdElemetosA;
} HeaderA;

typedef struct decolagem{
    char codigoDeVooD[7];
    char tipoDeVooD[2];
} Decolagem;

typedef struct listaDecolagem{
	void *decolagem;	
	struct listaDecolagem *proxD;
} ListaDecolagem;

typedef struct headerD{
	ListaDecolagem *headD; //ponteiro p o primero elemento da lista
	ListaDecolagem *tailD; //ponteiro p o ultimo elemento da lista
    int qntdElemetosD;
} HeaderD;

int numeroAprox();
int numeroDecolagem();
int numCombustivel();
int listaVazia(HeaderA *header);
int listaVaziaD(HeaderD *header);
int * randomizar(int n);
HeaderA *inicializaHeader1();
Pouso *novoPouso(char codigoDeVoo[7]);
void inserePouso(HeaderA *header, Pouso *pouso);
void visualizar(HeaderA *header);
HeaderD *inicializaHeaderD();
Decolagem *novaDecolagem(char codigoDeVoo[7]);
void insereDecolagem(HeaderD *header, Decolagem *decolagemS);
void visualizarD(HeaderD *header);
void mensagem1(int numapro, int numdeco, int numtotal,HeaderA *header);


int main (int argc, char *argv[]){
    HeaderA *inicioPouso = inicializaHeader1();
    HeaderD *iniciaDeco = inicializaHeaderD();
    char codigoDeVoo[64][7]={"VG3001" , "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
                             "AZ1008","AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", 
                             "AL0012","TT4544", "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", 
                             "AZ1002","AZ1007", "GL7604", "AZ1006", "TG1503", "AZ1003", "JJ4403", 
                             "AZ1001","LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502", "GL7601",
                             "TT4500","RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392",
                             "GF4681","GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065",
                             "LF0978","RL7867", "TT4502", "GL7645", "LF0932", "JJ4434", "TG1510",
                             "TT1020","AZ1098", "BA2312", "VG3030", "BA2304", "KL5609",
                             "KL5610","KL5611"};

    int numAprox = numeroAprox();
    int numDeco = numeroDecolagem();
    int numVoos= numAprox+numDeco;
    int *array;
    array = randomizar(numVoos);

    for(int i = 0; i<numAprox; i++){
        inserePouso(inicioPouso, novoPouso(codigoDeVoo[array[i]]));
    }
    
    mensagem1(numAprox, numDeco, numVoos,inicioPouso);

    for(int i = 0; i<numDeco; i++){
        insereDecolagem(iniciaDeco, novaDecolagem(codigoDeVoo[array[i]]));
    }
    visualizarD(iniciaDeco);
    return 0;
}

int numeroAprox(){
    srand(time(0));
    int numeroAprox = (rand() % 22) + 10;
    return numeroAprox;
}

int numeroDecolagem(){
    int numeroDecolagem = (rand() % 22) + 10;
    return numeroDecolagem;
}

int numCombustivel(){
    int numCombustivel = (rand()%12);
    return numCombustivel;
}

HeaderA *inicializaHeader1() {
	HeaderA *headerA = (HeaderA*) malloc(sizeof(HeaderA));;
    headerA->headA = NULL;
    headerA->tailA = NULL;
    headerA->qntdElemetosA = 0;
	return headerA;
}
Pouso *novoPouso(char codigoDeVoo[7]){
    Pouso * novoPouso= (Pouso*) malloc(sizeof(Pouso));
    if(novoPouso == NULL) {
        printf("Novo pouso não criado\n");
    }
    strcpy(novoPouso->codigoDeVooA, codigoDeVoo);
    strcpy(novoPouso->tipoDeVooA, "A");
    novoPouso->combustivel = numCombustivel();
}

void inserePouso(HeaderA *header, Pouso *pouso){
    ListaPouso *novoElemento = (ListaPouso*) malloc(sizeof(ListaPouso));
    if(novoElemento == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoElemento->pouso = pouso;
    header->qntdElemetosA++;

    if(header->headA == NULL) {
        header->headA = novoElemento;
        header->tailA = novoElemento;
        novoElemento->prox = NULL;
    }
    else {
        novoElemento->prox = NULL;
        header->tailA->prox = novoElemento;
        header->tailA = novoElemento;
    }

}

void visualizar(HeaderA *header) {
    ListaPouso *aux;
    if(listaVazia(header)) {
        printf("Lista vazia!\n\n");
        return;
    }
    for(aux = header->headA; aux != NULL; aux = aux->prox) {
        Pouso *pouso = (Pouso *)aux->pouso;
        printf("%s - %s - %d\n", pouso->codigoDeVooA, pouso->tipoDeVooA, pouso->combustivel);
    }
}

int listaVazia(HeaderA *header) {
    if(header->headA == NULL) {
        return true;
    }
    return false;
}

HeaderD *inicializaHeaderD() {
	HeaderD *headerD = (HeaderD*) malloc(sizeof(HeaderD));;
    headerD->headD = NULL;
    headerD->tailD = NULL;
    headerD->qntdElemetosD = 0;
	return headerD;
}
Decolagem *novaDecolagem(char codigoDeVoo[7]){
    Decolagem * novaDecolagem= (Decolagem*) malloc(sizeof(Decolagem));
    if(novaDecolagem == NULL) {
        printf("Novo pouso não criado\n");
    }
    strcpy(novaDecolagem->codigoDeVooD, codigoDeVoo);
    strcpy(novaDecolagem->tipoDeVooD, "D");
}

void insereDecolagem(HeaderD *header, Decolagem *decolagem){
    ListaDecolagem *novoEleDeco = (ListaDecolagem*) malloc(sizeof(ListaDecolagem));
    if(novoEleDeco == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoEleDeco->decolagem = decolagem;
    header->qntdElemetosD++;

    if(header->headD == NULL) {
        header->headD = novoEleDeco;
        header->tailD = novoEleDeco;
        novoEleDeco->proxD = NULL;
    }
    else {
        novoEleDeco->proxD = NULL;
        header->tailD->proxD = novoEleDeco;
        header->tailD = novoEleDeco;
    }

}

void visualizarD(HeaderD *header) {
    ListaDecolagem *auxD;
    
    printf("---------------------------------- \n");
    printf("          Lista de Decolagem       \n");    
    printf("----------------------------------\n");
    
    if(listaVaziaD(header)) {
        printf("Lista vazia!\n\n");
        return;
    }

    for(auxD = header->headD; auxD != NULL; auxD = auxD->proxD) {
        Decolagem *decolagem = (Decolagem *)auxD->decolagem;
        printf("Codigo do voo: %s\n", decolagem->codigoDeVooD);
        printf("tipoDeVoo: %s\n", decolagem->tipoDeVooD);
    }
}

int listaVaziaD(HeaderD *header) {
    if(header->headD == NULL) {
        return true;
    }
    return false;
}

int * randomizar(int n){

    srand(time(0));
	int i;
    int * array = (int *) calloc (n, sizeof (int));
    for (i = 0; i < n; ++i) {
        array[i] = i;
    }
 	for ( i = 0; i < n; i++) {
    	int temp = array[i];
   		int randomIndex = rand() % n;
  		array[i]= array[randomIndex];
    	array[randomIndex] = temp;
	}
    return array;
}

void mensagem1(int numapro, int numdeco, int numtotal,HeaderA *header){
    printf("Aeroporto Internacional de Brasilia\n");
    printf("Hora incial:\n");
    printf("Fila de Pedidos:\n");
    visualizar(header);
    printf("Numero de voos:%d\n", numtotal);
    printf("Numero de aproximações:%d\n", numapro);
    printf("Numero de decolagens:%d\n", numdeco);

}