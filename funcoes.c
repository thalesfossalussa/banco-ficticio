#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "funcoes.h"

void info(void){
    printf("\n\n\n\nPrograma feito como trabalho final da materia de AED1 pelo curso de Ciencias da Computacao, UFG\nCriadores:Joao Paulo Lopes de Carvalho Grilo e Thales fossalussa\n11/2020\n\n\n\n");
}

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
    if ((atual != NULL) && (atual->reg.cpf == cpf)) return atual;
    return NULL;
}

void inserirConta(BANCO* l) {
    PONT i, ant;
    char nome[30];
    int tam, senha1, senha2, c=0;
    tam = tamanhoBanco(l);
    ant = l->inicio;
    
    while(ant->prox!=NULL) ant = ant->prox; //acha o ultimo elemento da lista que aponta para NULL
    
    i = (PONT) malloc(sizeof(ELEMENTO)); //aloca nova conta
    ant->prox=i; //faz com que o antigo ultimo elemento aponte para a nova conta, que se torna o novo ultimo elemento

    if (tam == 0) { //caso a lista esteja vazia faz com que o começo seja a nova conta e aponta o prox como null
        l->inicio = i;
        i->prox = NULL;
    } else {
        i->prox = NULL;
    }   //processo de alocação de memória feito, agora para o preenchimento de dados

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Ok, para comecarmos nos diga o seu nome:\n");
    scanf("%s", nome);
    while(c=0){
        printf("Senhor(a) %s\nCaso tenha errado, basta digitar 0, caso esteja correto, digite 1", i->reg.nome);
        scanf("%d", &c);
    }
    strncpy(i->reg.nome, nome, 30);

    printf("Que otimo que decidiu se juntar a nos, %s. Por favor, informe-nos dos seus seguintes dados:\n\n", i->reg.nome);
    printf("CPF:\n");
    scanf("%d", &i->reg.cpf);
    while(i->reg.cpf>9999999999){ //caso o cpf tenha menos de 11 dígitos ele não será aceito, funciona já que não há cpf que comece com 0
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("|CPF invalido! Por favor, insira novamente.|\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        scanf("%d", &i->reg.cpf);
    }
    
    printf("Sua data de nascimento no seguinte formato dd mm aaaa:\n");
    scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    while((!i->reg.dia>0) && (!i->reg.dia<31) && (!i->reg.mes>0) && (!i->reg.mes<12) && (!i->reg.ano>2012)){ //não fiz casos especiais para ano bisexto e essas paradas, se quiser dar uma olhada nisso fique a vontade, da pra colocar uns if's no while tranquilamente
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("|Data de nasciemento invalida! Por favor, insira novamente.|\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    }

    i->reg.conta=i->reg.cpf*i->reg.ano/1000000000; //gerando um número de conta com 5 dígitos, quando o cpf começa com 499.... essa conta gera 6 números
    if(i->reg.conta>99999) i->reg.conta=i->reg.conta/10;//considerando que a conta máxima pode ser 201199, faz se necessária essa divisão
    
    printf("Media salarial mensal:\n");
    scanf("%d", &i->reg.salario);
    i->reg.saldo=i->reg.salario;
    i->reg.credito=i->reg.salario*0.2;
    i->reg.divida=0;


    printf("Ok, %d, agora para algumas informacoes sobre sua conta.\nSeu numero de conta e >%d<\nPor favor, Crie uma senha de 4 digitos:\n", i->reg.ano, i->reg.conta);
    scanf("%d", &senha1);
    while(1){
        printf("Confirme sua senha:\n");
        scanf("%d", &senha2);
        if(senha2==0) {
            printf("Nova senha:\n");
            scanf("%d", &senha1);
        }
        else{
            if(senha1==senha2){
                i->reg.senha=senha1;    
                break;
            }
            else{
                printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
                printf("|As senhas não batem. Tente novamente ou digite >0< para recriar a senha.|\n");
                printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
            }
        }
    }
    printf("Confirmado!\n\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|Seja bem vindo ao banco Pequi, %s, para mais informacoes, acessar a opcao *info* no menu inicial. O banco Pequi agradece sua escolha|\n", nome);
    printf("|--------------------------------------------------------------------------------------------------------------------------------|\n\n\n");

    return;
}

void excluirConta(BANCO* l, int cpf) { //busca o cpf do titular para exluir a conta
    PONT ant, atual;
    atual = l->inicio;
    ant = NULL;
    while(atual->reg.cpf!=cpf){ //caso os cpfs não batam o laço continua
        ant=atual; //o anterior se torna o atual   
        atual=atual->prox; //o atual se torna o próximo
    }
    if (ant == NULL) l->inicio = l->inicio->prox; //caso o anterior seja NULL, o atual já é o primeiro, logo só informamos que a lista começa a partir do segundo elemento
    else ant->prox = atual->prox; //caso o anterior não seja null, informamos que o próximo dele será o próximo do próximo, pulando uma posição que será exluída 
    free(atual); //excluíndo posição
}


void operacoes(BANCO* l, int nconta){
    int a=0, pagamento;
    PONT conta=l->inicio;
    while(conta->prox!=NULL){
        if(conta->reg.conta==nconta) break;
        conta=conta->prox;
    }

    printf("-----------------------------------------------------------\n");
    printf("O que deseja fazer?");
    printf("Digite 1 para saber seu saldo\n.");
    printf("Digite 2 para realizar um pagamento\n.");
    printf("Digite 3 para realizar um saque\n.");
    printf("Digite 4 para realizar uma transferencia\n.");
    printf("Digite 5 para consultar seu credito.\n");
    printf("Digite 6 para realizar um pagamento com credito.\n");
    printf("Digite 7 para realizar o pagamento da sua conta de credito.\n");
    printf("Digite 8 caso deseje encerrar sua conta.\n");
    printf("Digite 9 caso deseje sair.\n");
    printf("-----------------------------------------------------------\n");
    while((a<1) && (a>8)){
        scanf("%d", &a);
        switch (a)
        {
        case 1:
        printf("Seu saldo e de RS:%d.", conta->reg.saldo);
            break;
        case 2:
        printf("Voce tem RS:%d disponiveis\nValor do pagamento: ", conta->reg.saldo);
        scanf("%d", &pagamento);
        if(pagamento>conta->reg.saldo) printf("Sem saldo disponivel!\n"); 
        else{
            conta->reg.saldo=(conta->reg.saldo) - pagamento;
            printf("\nSeu novo saldo e de RS:%d", conta->reg.saldo);
        }
            break;
        case 3:
        printf("Voce tem RS:%d disponiveis\nValor do saque: ", conta->reg.saldo);
        scanf("%d", &pagamento);
        if(pagamento>conta->reg.saldo) printf("Sem saldo disponivel!\n"); 
        else{
            conta->reg.saldo=(conta->reg.saldo) - pagamento;
            printf("\nSeu novo saldo e de RS:%d", conta->reg.saldo);
        }
            break;
        case 4:
            break;
        case 5:
        printf("Seu limite é de RS:%d.", conta->reg.credito);
            break;
        case 6:
        printf("Voce tem RS:%d de credito disponivel\nValor do pagamento: ", conta->reg.credito-conta->reg.divida);
        scanf("%d", &pagamento);
        if((conta->reg.divida + pagamento)>conta->reg.credito) printf("Sem credito disponivel!\n"); 
        else{
            conta->reg.divida=(conta->reg.divida) + pagamento;
            printf("\nCredito disponivel RS:%d.", conta->reg.saldo - conta->reg.divida);
        }
            break;
        case 7:
        printf("Voce tem um total de RS%d de credito a ser pago.\nDeseja pagar? (1 para sim | 0 para não)\n", conta->reg.divida);
        scanf("%d", &pagamento);
        if(pagamento==0) break;
        if(pagamento==1){
            if(conta->reg.divida>conta->reg.saldo) printf("Sem saldo disponivel!\n");
            else{
                conta->reg.saldo=conta->reg.saldo-conta->reg.divida;
                printf("Pagamento feito com sucesso!\nNovo saldo disponivel RS:%d.",conta->reg.saldo);
            }
        }
            break;
        case 8:
            break;
        case 9:
            printf("Obrigado, volte sempre.\n");
            return ;
            break;
        default:
            printf("Operacao invalida, tente novamente\n");
            break;
        }
    }
}

void login(BANCO* l){ //busca pelo banco uma conta que tenha o nconta e senha iguais aos informados
    int nconta, senha, v=0;
    PONT conta;
    while(v=0){ //v é o verificador, caso permaneça em 0 significa que nenhuma conta regitrada foi encontrada 
        conta=l->inicio;
        printf("Digite seu numero de conta e senha:\n");
        scanf("%d %d",&nconta, &senha);
        
        while(conta->prox!=NULL){ //percorre as structs
            if ((nconta==conta->reg.conta) && (senha==conta->reg.senha)){ //caso onde as informações batem 
                printf("seja bem vindo(a) %s!\n",conta->reg.nome);
                v++; //verificador incrementado e laço quebrado
                operacoes(l, conta->reg.conta);
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

void printMenu(void) {
    printf("---------------------------------\n");
	printf("Menu\n");
    printf("---------------------------------\n");
	printf("1 - Acessar sua conta\n");
    printf("---------------------------------\n");
	printf("2 - Criar sua conta\n");
    printf("---------------------------------\n");
	printf("3 - Proximo mes\n");
    printf("---------------------------------\n");
    printf("4 - Informacoes\n");
    printf("---------------------------------\n");
    printf("5 - fechar\n");
    printf("---------------------------------\n");
}