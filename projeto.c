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
typedef struct nodePouso{
	void *pouso;	
	struct nodePouso *prox;
} NodePouso;

// cabeçalho de pouso
typedef struct headerA{
	NodePouso *inicioA; //ponteiro p o primero elemento da lista
	NodePouso *finalA; //ponteiro p o ultimo elemento da lista
    int qntdElemetosA;
} HeaderA;

typedef struct decolagem{
    char codigoDeVooD[7];
    char tipoDeVooD[2];
} Decolagem;

typedef struct nodeDecolagem{
	void *decolagem;	
	struct nodeDecolagem *proxD;
} NodeDecolagem;

typedef struct headerD{
	NodeDecolagem *inicioD; //ponteiro p o primero elemento da lista
	NodeDecolagem *finalD; //ponteiro p o ultimo elemento da lista
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
void mensagem1(int numapro, int numdeco, int numtotal,HeaderA *header, HeaderD *header2,int);
void ordena (HeaderA *header);
void printaA(HeaderA *listaA, int horario, int pista);
void printaD(HeaderD *listaD, int horario, int pista);
void retiraD(HeaderD *listaD);
void retiraA(HeaderA *listaA);
void pistas(HeaderA *listaA, HeaderD *listaD, int horas);
void decreCombs(HeaderA *listaA);

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
    int hora = 480; //8 horas
    array = randomizar(numVoos);

    for(int i = 0; i<numAprox; i++){
        inserePouso(inicioPouso, novoPouso(codigoDeVoo[array[i]]));
    }
   

    for(int i = 0; i<numDeco; i++){
        insereDecolagem(iniciaDeco, novaDecolagem(codigoDeVoo[array[i]]));
    }

    ordena (inicioPouso);
    mensagem1(numAprox, numDeco, numVoos,inicioPouso,iniciaDeco, hora); 

    pistas(inicioPouso, iniciaDeco, hora);
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
    headerA->inicioA = NULL;
    headerA->finalA = NULL;
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
    return novoPouso;
}

void inserePouso(HeaderA *header, Pouso *pouso){
    NodePouso *novoElemento = (NodePouso*) malloc(sizeof(NodePouso));
    if(novoElemento == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoElemento->pouso = pouso;
    header->qntdElemetosA++;

    if(header->inicioA == NULL) {
        header->inicioA = novoElemento;
        header->finalA = novoElemento;
        novoElemento->prox = NULL;
    }
    else {
        novoElemento->prox = NULL;
        header->finalA->prox = novoElemento;
        header->finalA = novoElemento;
    }

}

void visualizar(HeaderA *header) {
    NodePouso *aux;
    if(listaVazia(header)) {
        printf("Lista vazia!\n\n");
        return;
    }
    for(aux = header->inicioA; aux != NULL; aux = aux->prox) {
        Pouso *pouso = (Pouso *)aux->pouso;
        printf("%s - %s - %d\n", pouso->codigoDeVooA, pouso->tipoDeVooA, pouso->combustivel);
    }
}

int listaVazia(HeaderA *header) {
    if(header->inicioA == NULL) {
        return true;
    }
    return false;
}

HeaderD *inicializaHeaderD() {
	HeaderD *headerD = (HeaderD*) malloc(sizeof(HeaderD));;
    headerD->inicioD = NULL;
    headerD->finalD = NULL;
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
    return novaDecolagem;
}

void insereDecolagem(HeaderD *header, Decolagem *decolagem){
    NodeDecolagem *novoEleDeco = (NodeDecolagem*) malloc(sizeof(NodeDecolagem));
    if(novoEleDeco == NULL) {
        printf("Pouso nao pode ser inserido na lista!\n");
    }

    novoEleDeco->decolagem = decolagem;
    header->qntdElemetosD++;

    if(header->inicioD == NULL) {
        header->inicioD = novoEleDeco;
        header->finalD = novoEleDeco;
        novoEleDeco->proxD = NULL;
    }
    else {
        novoEleDeco->proxD = NULL;
        header->finalD->proxD = novoEleDeco;
        header->finalD = novoEleDeco;
    }

}

void visualizarD(HeaderD *header) {
    NodeDecolagem *aux;
    if(listaVaziaD(header)) {
        printf("Lista vazia!\n\n");
        return;
    }
    for(aux = header->inicioD; aux != NULL; aux = aux->proxD) {
        Decolagem *decolagem = (Decolagem *)aux->decolagem;
        printf("%s - %s\n", decolagem->codigoDeVooD, decolagem->tipoDeVooD);
    }
}

int listaVaziaD(HeaderD *header) {
    if(header->inicioD == NULL) {
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

void mensagem1(int numapro, int numdeco, int numtotal,HeaderA *header, HeaderD *header2, int horas){
    printf("Aeroporto Internacional de Brasilia\n");
    printf("Hora incial: %d:%d\n", horas/60, horas%60);
    printf("Fila de Pedidos:\n");
    visualizar(header);
    visualizarD(header2);
    printf("Numero de voos:%d\n", numtotal);
    printf("Numero de aproximações:%d\n", numapro);
    printf("Numero de decolagens:%d\n", numdeco);

}

void ordena (HeaderA *header){
    char tempCodigo[7];
    int tempCombustivel;
    if(listaVazia(header) == true){
        return;
    }
    NodePouso *p1 = (NodePouso*) malloc(sizeof(NodePouso));
    NodePouso *p2 = (NodePouso*) malloc(sizeof(NodePouso));

    for(int k = 0; k<((header->qntdElemetosA)-1); k++){

        p1 = (NodePouso *)header->inicioA;

        for (int i = 0; i <((header->qntdElemetosA)-1); i++){ 

            p2 = (NodePouso *)p1->prox;
            Pouso * a = (Pouso *)p1->pouso;
            Pouso * b = (Pouso *)p2->pouso;
            if (a->combustivel > b->combustivel){
                strcpy(tempCodigo, a->codigoDeVooA);
                tempCombustivel= a->combustivel;
                strcpy(a->codigoDeVooA, b->codigoDeVooA);
                a->combustivel = b->combustivel;
                strcpy(b->codigoDeVooA, tempCodigo);
                b->combustivel = tempCombustivel;
            }
            p1 = p1->prox;

        }
    }
    //free(p1);
    //free(p2);
}

void pistas(HeaderA *listaA, HeaderD *listaD, int horas){
    int incrementa = 5;
    int contadorCombs = 0;
    int pista1=0,pista2=0,pista3=0;// 0 = liberado
    int pouso = 0;
    int decolagem = 0;
    printf("\n");
    printf("Lista de eventos:\n");
    printf("\n");
    int condicao= 0;
    while(condicao==0){
         if(listaA->inicioA==NULL && listaD->inicioD==NULL){
            condicao=1;
        }
        else{
            if (pista1 == 0){
                if(listaA->inicioA != NULL){ //aterriza
                    pista1 = 3;
                    pouso++;
                    printaA(listaA, horas,1);
                    retiraA(listaA);
                }
                else if(listaD->inicioD != NULL){//decola
                    pista1 = 1;
                    decolagem++;
                    printaD(listaD,horas,1);
                    retiraD(listaD);
                }
            }
            else{
                pista1--;
            }

            if (pista2 == 0){ //aterriza
                if(listaA->inicioA != NULL){
                    pouso++;
                    pista2 = 3;
                    printaA(listaA, horas,2);
                    retiraA(listaA);
                }
                else if(listaD->inicioD != NULL){//decola
                    pista2 = 1;
                    decolagem++;
                    printaD(listaD,horas,2);
                    retiraD(listaD);
                }
            }
            else{
                pista2--;
            }

            if(pista3 == 0){
                if(listaA->inicioA != NULL){
                    Pouso *pouso = (Pouso*)listaA->inicioA->pouso;
                    if(pouso->combustivel == 0){
                        printf("\n ALERTA GERAL DE DESVIO DE AERONAVE\n");
                        pista3 = 3;
                        pouso++;
                        printaA(listaA, horas,3);
                        retiraA(listaA);
                    }
                    else if(listaD->inicioD != NULL){
                        pista3 = 1;
                        decolagem++;
                        printaD(listaD,horas,3);
                        retiraD(listaD);
                    }
                }
                else if(listaD->inicioD != NULL){
                    pista3 = 1;
                    decolagem++;
                    printaD(listaD,horas,3);
                    retiraD(listaD);
                }

            }
            else{
                pista3--;
            }
            NodePouso *nodepouso = (NodePouso *)listaA->inicioA;
            for (int i = 0; i <(listaA->qntdElemetosA); i++){
                Pouso *pouso2 = (Pouso*)nodepouso->pouso;
                if((pouso2->combustivel) == 0){
                    printf("\nALERTA CRITICO, AERONAVE IRA CAIR\n");
                    retiraA(listaA);
                    nodepouso = nodepouso->prox;    
                }   
            }  
            contadorCombs ++;
            horas += incrementa;

            if(contadorCombs%10 == 0){
                decreCombs(listaA);
            }
        }
    }
}

void retiraA(HeaderA *listaA){
    NodePouso *primeroPouso = (NodePouso *)listaA->inicioA;
    listaA->inicioA = primeroPouso->prox;
    listaA->qntdElemetosA--;
    free(primeroPouso);
}

void retiraD(HeaderD *listaD){
    NodeDecolagem *primeraDeco = (NodeDecolagem *)listaD->inicioD;
    listaD->inicioD = primeraDeco->proxD;
    listaD->qntdElemetosD--;
    free(primeraDeco);
}

void printaA(HeaderA *listaA, int horario, int pista){
    char codigoDeVoo[7];
    Pouso *pouso = (Pouso *)listaA->inicioA->pouso;
    strcpy(codigoDeVoo,pouso->codigoDeVooA);
     printf("\n");
    printf("Codigo de voo: %s\n", codigoDeVoo);
    printf("Status: aeronave pouso\n");
    if(horario%60 == 0){
        printf("Horario do inicio do procedimento: %d:00\n", horario/60);
    }
    else{
        printf("Horario do inicio do procedimento: %d:%d\n", horario/60, horario%60);
    }
    printf("Numero da pista: %d\n", pista);
}

void printaD(HeaderD *listaD, int horario, int pista){
    char codigoDeVoo[7];
    Decolagem *decolagem = (Decolagem *)listaD->inicioD->decolagem;
    strcpy(codigoDeVoo,decolagem->codigoDeVooD);
    printf("\n");
    printf("Codigo de voo: %s\n", codigoDeVoo);
    printf("Status: aeronave decolou\n");
    if (horario%60 == 0){
        printf("Horario do inicio do procedimento: %d:00\n", horario/60);
    }
    else{
        printf("Horario do inicio do procedimento: %d:%d\n", horario/60, horario%60);
    }
    printf("Numero da pista: %d\n", pista);
}

void decreCombs(HeaderA *listaA){
    NodePouso *nodepouso = (NodePouso *)listaA->inicioA;
    for (int i = 0; i <(listaA->qntdElemetosA); i++){
        Pouso *pouso = (Pouso*)nodepouso->pouso;
        pouso->combustivel = (pouso->combustivel-1);
        nodepouso = nodepouso->prox;        
    }
}