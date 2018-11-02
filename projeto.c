#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define true 1
#define false 0

typedef struct pouso{
    char codigoDeVoo[7];
    char tipoDeVoo[2];
    int combustivel;
} Pouso;

//lista de pouso
typedef struct listaPouso{
	void *pouso;	
	struct lista1 *prox;
} ListaPouso;

// cabeçalho de pouso
typedef struct header1{
	ListaPouso *head; //ponteiro p o primero elemento da lista
	ListaPouso *tail; //ponteiro p o ultimo elemento da lista
    int qntdElemetos;
} Header1;

typedef struct decolagem{
    char codigoDeVoo[7];
    char tipoDeVoo[2];
} Decolagem;

//lista da decolagem
typedef struct listaDecolagem{
	void *decolagem;	
	struct lista1 *prox;
} ListaDecolagem;

// cabeçalho da decolagem
typedef struct header2{
	ListaDecolagem *head; //ponteiro p o primero elemento da lista
	ListaDecolagem *tail; //ponteiro p o ultimo elemento da lista
    int qntdElemetos;
} Header2;


int numeroAprox();
int numeroDecolagem();
int numCombustivel();
Header1 *inicializaHeader1();
Pouso *novoPouso(char codigoDeVoo[7]);
void inserePouso(Header1 *header, Pouso *pouso);
void insereDecolagem(Header2 *header, Decolagem *decolagem);
void visualizar(Header1 *header);
void visualizar2(Header2 *header);
int listaVazia(Header1 *header);
int listaVazia2(Header2 *header);
Header2 *inicializaHeader2();
Decolagem *novaDecolagem(char codigoDeVoo[7]);

int main (int argc, char *argv[]){
    Header1 *inicioPouso = inicializaHeader1();
    Header2 *inicioDecolagem = inicializaHeader2();

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

    for(int i = 0; i<numAprox; i++){
        inserePouso(inicioPouso, novoPouso(codigoDeVoo[i]));
    }
    printf("Numero de pousos %d\n", inicioPouso->qntdElemetos);
    visualizar(inicioPouso);

    for(int i = 0; i<numDeco; i++){
        insereDecolagem(inicioDecolagem, novaDecolagem(codigoDeVoo[i+numAprox]));
    }
    printf("Numero de decolagem %d\n", inicioDecolagem->qntdElemetos);
    visualizar2(inicioDecolagem);

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

Header1 *inicializaHeader1() {
	Header1 *header1 = (Header1*) malloc(sizeof(Header1));;
    header1->head = NULL;
    header1->tail = NULL;
    header1->qntdElemetos = 0;
	return header1;
}

Header2 *inicializaHeader2() {
	Header2 *header2 = (Header2*) malloc(sizeof(Header2));;
    header2->head = NULL;
    header2->tail = NULL;
    header2->qntdElemetos = 0;
	return header2;
}

Pouso *novoPouso(char codigoDeVoo[7]){
    Pouso * novoPouso= (Pouso*) malloc(sizeof(Pouso));
    if(novoPouso == NULL) {
        printf("Novo pouso não criado\n");
    }
    strcpy(novoPouso->codigoDeVoo, codigoDeVoo);
    strcpy(novoPouso->tipoDeVoo, "A");
    novoPouso->combustivel = numCombustivel();
}

Decolagem *novaDecolagem(char codigoDeVoo[7]){
    Decolagem * novaDecolagem= (Decolagem*) malloc(sizeof(Decolagem));
    if(novaDecolagem == NULL) {
        printf("Nova decolagem não criado\n");
    }
    strcpy(novaDecolagem->codigoDeVoo, codigoDeVoo);
    strcpy(novaDecolagem->tipoDeVoo, "D");
}

void inserePouso(Header1 *header, Pouso *pouso){
    ListaPouso *novoElemento = (ListaPouso*) malloc(sizeof(ListaPouso));
    if(novoElemento == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoElemento->pouso = pouso;
    header->qntdElemetos++;

    if(header->head == NULL) {
        header->head = novoElemento;
        header->tail = novoElemento;
        novoElemento->prox = NULL;
    }
    else {
        novoElemento->prox = NULL;
        header->tail->prox = novoElemento;
        header->tail = novoElemento;
    }

}

void insereDecolagem(Header2 *header, Decolagem *decolagem){
    ListaDecolagem *novoElemento = (ListaDecolagem*) malloc(sizeof(ListaDecolagem));
    if(novoElemento == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoElemento->decolagem = decolagem;
    header->qntdElemetos++;

    if(header->head == NULL) {
        header->head = novoElemento;
        header->tail = novoElemento;
        novoElemento->prox = NULL;
    }
    else {
        novoElemento->prox = NULL;
        header->tail->prox = novoElemento;
        header->tail = novoElemento;
    }

}

void visualizar(Header1 *header) {
    ListaPouso *aux;
    
    printf("---------------------------------- \n");
    printf("          Lista de Pouso       \n");    
    printf("----------------------------------\n");
    
    if(listaVazia(header)) {
        printf("Lista vazia!\n\n");
        return;
    }

    for(aux = header->head; aux != NULL; aux = aux->prox) {
        Pouso *pouso = (Pouso *)aux->pouso;
        printf("Codigo do voo: %s\n", pouso->codigoDeVoo);
        printf("tipoDeVoo: %s\n", pouso->tipoDeVoo);
        printf("Combustivel: %d\n", pouso->combustivel);
    }
}

void visualizar2(Header2 *header) {
    ListaDecolagem *aux2;
    
    printf("---------------------------------- \n");
    printf("          Lista de Decolagem      \n");    
    printf("----------------------------------\n");
    
    if(listaVazia2(header)) {
        printf("Lista vazia!\n\n");
        return;
    }

    for(aux2 = header->head; aux2 != NULL; aux2 = aux2->prox) {
        Decolagem *decolagem = (Decolagem *)aux2->decolagem;
        printf("Codigo do voo: %s\n", decolagem->codigoDeVoo);
        printf("tipoDeVoo: %s\n", decolagem->tipoDeVoo);
    }
}



int listaVazia(Header1 *header) {
    if(header->head == NULL) {
        return true;
    }
    return false;
}

int listaVazia2(Header2 *header) {
    if(header->head == NULL) {
        return true;
    }
    return false;
}