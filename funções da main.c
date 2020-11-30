#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct {
    char nome[30];
    int cpf;
    int dia;
    int mes;
    int ano;
    int salario;
    int saldo;
    int credito;
    int divida;
    int conta;
    int senha;
} REGISTRO; //struct que abriga os dados da conta/registro do cliente
    
typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO; 

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} BANCO;

void inicializarBanco(BANCO* l){
l->inicio = NULL;
}

int tamanhoBanco(BANCO* l) {
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL) {
    tam++;
    end = end->prox;
    }
    return tam;
}

PONT buscarConta(BANCO* l, int cpf, PONT* ant){ //retorna o pontero que aponta para a conta desejada
    *ant = NULL;
    PONT atual = l->inicio;
    while ((atual != NULL) && (atual->reg.cpf!=cpf)) {
    *ant = atual;
    atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == ch)) return atual;
    return NULL;
}

void inserirConta(BANCO* l) {
    PONT i, ant;
    int tam;
    int cpf, dd, mm, aaaa, sal, conta, senha1, senha2, cred, c=0;
    tam = tamanhoBanco(l);
    ant = l->inicio;
    
    while(ant-prox!=NULL) ant = ant->prox; //acha o ultimo elemento da lista que aponta para NULL
    
    i = (PONT) malloc(sizeof(ELEMENTO)); //aloca nova conta
    ant->prox=i; //faz com que o antigo ultimo elemento aponte para a nova conta, que se torna o novo ultimo elemento

    if (tam == 0) { //caso a lista esteja vazia faz com que o começo seja a nova conta e aponta o prox como null
        l->inicio = i;
        i->prox = NULL;
    } else {
        i->prox = NULL;
    }

    return;
}

void excluirConta(BANCO* l, int cpf) { //busca o cpf do titular para exluir a conta
    PONT ant, atual;
    atual = l->inicio;
    ant = NULL;
    while(i->reg.cpf!=cpf){ //caso os cpfs não batam o laço continua
        ant=atual; //o anterior se torna o atual   
        atual=atual->prox; //o atual se torna o próximo
    }
    if (ant == NULL) l->inicio = l->prox; //caso o anterior seja NULL, o atual já é o primeiro, logo só informamos que a lista começa a partir do segundo elemento
    else ant->prox = atual->prox; //caso o anterior não seja null, informamos que o próximo dele será o próximo do próximo, pulando uma posição que será exluída 
    free(i); //excluíndo posição
}

void login(BANCO* l){ //busca pelo banco uma conta que tenha o nconta e senha iguais aos informados
    int nconta, senha, v=0;
    PONT conta;
    while(v=0){ //v é o verificador, caso permaneça em 0 significa que nenhuma conta regitrada foi encontrada 
        conta=l->inicio;
        pritf("Digite seu numero de conta e senha:\n");
        scanf("%d %d",&nconta, &senha);
        
        while(conta->prox!=NULL){ //percorre as structs
            if ((nconta==conta->reg.conta) && (senha==conta->reg.senha)){ //caso onde as informações batem 
                printf("senha bem vindo(a) %s!\n",conta->reg.nome);
                v++; //verificador incrementado e laço quebrado
                operacoes(&conta);
                break;
            }
            conta=conta->prox; //caso onde as informações não batem
        }
        if(v!=0) break;
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("Numero de conta ou senha incorretos ou inexistentes, tente novamente.\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n"); //ciclo recomeçado
    }
}

void operacoes(BANCO* l){
    int a=0;
    printf("-----------------------------------------------------------\n");
    printf("Digite 1 para saber seu saldo\n.");
    printf("Digite 2 para realizar um pagamento\n.");
    printf("Digite 3 para realizar um saque\n.");
    printf("Digite 4 para realizar uma transferencia\n.");
    printf("Digite 5 para consultar seu credito.\n");
    printf("Digite 6 para realizar um pagamento com credito.\n");
    printf("Digite 7 para realizar o pagamento da sua conta de credito.\n");
    printf("Digite 8 caso deseje encerrar sua conta.\n")
    printf("-----------------------------------------------------------\n");
    while((a<1) && (a>8)){
        scanf("%d", &a);
        if((a<1) && (a>8)) printf("Opção invalida. Tente novamente.\n")
    }
}