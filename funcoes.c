#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "funcoes.h"

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
    int tam, senha1, senha2, c=0;
    float cpf;
    tam = tamanhoBanco(l);
    ant = l->inicio;

    i = (PONT) malloc(sizeof(ELEMENTO)); //aloca nova conta
    
    if (tam == 0) { //caso a lista esteja vazia faz com que o começo seja a nova conta e aponta o prox como null
        l->inicio = i;
        i->prox = NULL;
    } else {
        while(ant->prox!=NULL) ant = ant->prox; //acha o ultimo elemento da lista que aponta para NULL
        ant->prox=i; //faz com que o antigo ultimo elemento aponte para a nova conta, que se torna o novo ultimo elemento
        i->prox = NULL;
    }  //processo de alocação de memória feito, agora para o preenchimento de dados

    printf("-------------------------------------------------------------------------------\n");
    printf("Ok, para comecarmos nos diga o seu nome:\n");
    while(1){
        scanf("%s", i->reg.nome);
        printf("Senhor(a) %s?\nCaso tenha errado, basta digitar o nome correto, caso esteja correto, digite 1:\nOpcao:", i->reg.nome);
        scanf("%d", &c);
        if(c==0) printf("Nome: ");
        if(c==1) break;
    }

    printf("\nSeu CPF:");
    scanf("%ld", &i->reg.cpf);
    while(i->reg.cpf>99999999999 || i->reg.cpf<10000000000){ //caso o cpf tenha menos de 11 dígitos ele não será aceito, funciona já que não há cpf que comece com 0
        printf("\n==========================================\n");
        printf("CPF invalido! Por favor, insira novamente.\n");
        printf("==========================================\n");
        scanf("%ld", &i->reg.cpf);
    }
    printf("\n*%ld*\n", i->reg.cpf);
    printf("\nSua data de nascimento no seguinte formato dd mm aaaa:");
    scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    while(i->reg.dia<1 || i->reg.dia>31 || i->reg.mes<1 || i->reg.mes>12 || i->reg.ano>2002){ //não fiz casos especiais para ano bisexto e essas paradas, se quiser dar uma olhada nisso fique a vontade, da pra colocar uns if's no while tranquilamente
        printf("\n==========================================================\n");
        printf("Data de nasciemento invalida! Por favor, insira novamente.\n");
        printf("==========================================================\n");
        scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    }

    i->reg.conta=i->reg.cpf*i->reg.ano/1000000000; //gerando um número de conta com 5 dígitos, quando o cpf começa com 499.... essa conta gera 6 números
    while(i->reg.conta>99999) i->reg.conta=i->reg.conta/10;//considerando que a conta máxima pode ser 201199, faz se necessária essa divisão
    
    printf("\nSalario mensal:");
    scanf("%e", &i->reg.salario);
    i->reg.saldo=i->reg.salario;
    i->reg.credito=i->reg.salario*0.2;
    i->reg.divida=0;

    printf("\nOk, %s, agora para algumas informacoes sobre sua conta.\nSeu numero de conta e >%d<.\n\nAgora digite uma senha de 4 digitos: ", i->reg.nome, i->reg.conta);
    scanf("%d", &senha1);
    while(1){
        while(senha1>9999 || senha1<1000){
            printf("Senha invalida! Tente, novamente.\nNova senha:");
            scanf("%d", &senha1);
        }
        printf("\nConfirme sua senha: ");
        scanf("%d", &senha2);
        if(senha2==0) {
            printf("Nova senha:");
            scanf("%d", &senha1);
            while(senha1>9999 || senha1<1000){
            printf("Senha invalida! Tente, novamente.\nNova senha:");
            scanf("%d", &senha1);
        }
        }
        else{
            if(senha1==senha2){
                i->reg.senha=senha1;    
                break;
            }
            else{
                printf("\n========================================================================\n");
                printf("As senhas nao batem. Tente novamente ou digite >0< para recriar a senha.\n");
                printf("========================================================================\n");

            }
        }
    }

    printf("Confirmado!\n\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Seja bem vindo ao banco Pequi, %s, para mais informacoes, acessar a opcao *info* no menu inicial. O banco Pequi agradece sua escolha\n", i->reg.nome);
    printf("--------------------------------------------------------------------------------------------------------------------------------------\n\n");

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

void transferencia(BANCO* l, int transferido){
    int ctrans;
    PONT cont = l->inicio;
    printf("Digite o numero da conta a receber a transferencia.\n");
    scanf("%d", &ctrans);
    while(cont->prox!=NULL){
        if(ctrans==cont->reg.conta){ 
        cont->reg.saldo=cont->reg.saldo+transferido;
        break;
        }
    }
    if(cont->prox==NULL){
        printf("Conta inexistente!\n");
        return ;
    }

}

void menuop(){
    printf("\n-----------------------------------------------------------\n");
    printf("O que deseja fazer?\n");
    printf("Digite 1 para saber seu saldo.\n");
    printf("Digite 2 para realizar um pagamento.\n");
    printf("Digite 3 para realizar um saque.\n");
    printf("Digite 4 para realizar uma transferencia.\n");
    printf("Digite 5 para consultar seu credito.\n");
    printf("Digite 6 para realizar um pagamento com credito.\n");
    printf("Digite 7 para realizar o pagamento da sua conta de credito.\n");
    printf("Digite 8 caso deseje encerrar sua conta.\n");
    printf("Digite 9 caso deseje sair.\n");
    printf("-----------------------------------------------------------\n");
    printf("Opcao: ");
}

void operacoes(BANCO* l, int nconta){
    int fechar=0, a=0, pagamento, csenha;
    float ccpf;
    PONT conta=l->inicio;
    while(conta->prox!=NULL){
        if(conta->reg.conta==nconta) break;
        conta=conta->prox;
    }
    while(fechar==0){
        menuop();
        scanf("%d", &a);
        switch (a)
        {
        case 1:
        printf("Seu saldo e de RS:%e.\n", conta->reg.saldo);
            break;
        
        case 2:
        printf("Voce tem RS:%f disponiveis\nValor do pagamento: ", conta->reg.saldo);
        scanf("%d", &pagamento);
        printf("\n");
        if(pagamento>conta->reg.saldo) printf("Saldo insuficiente!\n");
        else{
            conta->reg.saldo=(conta->reg.saldo) - pagamento;
            printf("\nSeu novo saldo e de RS:%f\n", conta->reg.saldo);
        }
            break;
        
        case 3:
        printf("Voce tem RS:%f disponiveis\nValor do saque: ", conta->reg.saldo);
        scanf("%d", &pagamento);
        printf("\n");
        if(pagamento>conta->reg.saldo) printf("Saldo insuficiente!\n");
        else{
            conta->reg.saldo=(conta->reg.saldo) - pagamento;
            printf("\nSeu novo saldo e de RS:%f", conta->reg.saldo);
        }
            break;
        
        case 4:
        printf("Voce tem RS:%f disponiveis\nValor a ser transferido RS:", conta->reg.saldo);
        scanf("%d", &pagamento);
        printf("\n");
        if(pagamento>conta->reg.saldo) printf("Saldo insuficiente!\n");
        else{
            conta->reg.saldo=conta->reg.saldo-pagamento;
            transferencia(l, pagamento);
        }

            break;
       
        case 5:
        printf("Seu limite é de RS:%f.\n", conta->reg.credito);
            break;
      
        case 6:
        printf("Voce tem RS:%f de credito disponivel\nValor do pagamento: ", conta->reg.credito-conta->reg.divida);
        scanf("%d", &pagamento);
        printf("\n");
        if((conta->reg.divida + pagamento)>conta->reg.credito) printf("Credito insuficiente!\n"); 
        else{
            conta->reg.divida=(conta->reg.divida) + pagamento;
            printf("\nCredito disponivel RS:%f.", conta->reg.saldo - conta->reg.divida);
        }
            break;
      
        case 7:
        printf("Voce tem um total de RS%f de credito a ser pago.\nDeseja pagar? (1 para sim | 0 para não)\n", conta->reg.divida);
        scanf("%d", &pagamento);
        if(pagamento==0) break;
        if(pagamento==1){
            if(conta->reg.divida>conta->reg.saldo) printf("Saldo insuficiente!\n");
            else{
                conta->reg.saldo=conta->reg.saldo-conta->reg.divida;
                printf("Pagamento feito com sucesso!\nNovo saldo disponivel RS:%f.\n",conta->reg.saldo);
            }
        }
            break;
    
        case 8:
        printf("Certo, primeiro precisamos que voce confirme seu cpf e data de nascimento\n");
        while(ccpf!=conta->reg.cpf || csenha!=conta->reg.senha){
            scanf("%f %d", &ccpf, &csenha);
            if(ccpf!=conta->reg.cpf || csenha!=conta->reg.senha){
                printf("Dados incorretos, deseja tentar novamente?\n(1 para sim, 0 para nao).\n");
                scanf("%d",&pagamento);
                printf("\n");
                if(pagamento==0) break;
                if(pagamento==1) scanf("%f %d", &ccpf, &csenha);
            } else { 
                excluirConta(l, conta->reg.cpf);
                printf("Obrigado pelo seu tempo conosto, ate breve.\n");
                return ;
            }
        }
            break;
 
        case 9:
            printf("Obrigado, volte sempre.\n");
            return ;
            break;
        default:
            printf("Operacao invalida, tente novamente.\n");
            break;
        }
    }
}

void login(BANCO* l){ //busca pelo banco uma conta que tenha o nconta e senha iguais aos informados
    int nconta, senha, v=0;
    PONT conta;
    while(v==0){ //v é o verificador, caso permaneça em 0 significa que nenhuma conta regitrada foi encontrada 
        conta=l->inicio;
        printf("Digite seu numero de conta e senha:\n");
        scanf("%d %d",&nconta, &senha);
        if(nconta==0) break;
        while(conta!=NULL){ //percorre as structs
            if ((nconta==conta->reg.conta) && (senha==conta->reg.senha)){ //caso onde as informações batem 
                printf("seja bem vindo(a) %s!\n",conta->reg.nome);
                v++; //verificador incrementado e laço quebrado
                operacoes(l, conta->reg.conta);
                break;
            }
            conta=conta->prox; //caso onde as informações não batem
        }
        if(v!=0) break;
        printf("\n=====================================================================\n");
        printf("Numero de conta ou senha incorretos ou inexistentes, tente novamente.\n");
        printf("=====================================================================\n"); //ciclo recomeçado
    }
}

void deposito(BANCO* l){
    PONT conta = l->inicio;
    while(conta->prox!=NULL){
        conta->reg.saldo=conta->reg.saldo+conta->reg.salario;
        conta=conta->prox;
    }
    if(conta->prox==NULL) conta->reg.saldo=conta->reg.saldo+conta->reg.salario;
    return ;
}

void limpa(BANCO* l){
    PONT end = l->inicio;
    while (end != NULL){
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

void imprime(BANCO* l){
    PONT mostra = l->inicio;
    while(mostra!=NULL){
        printf("cpf: %f", mostra->reg.cpf);
        printf("\nnome: %s", mostra->reg.nome);
        printf("\ndia: %d ", mostra->reg.dia);
        printf("mes: %d ", mostra->reg.mes);
        printf("ano: %d", mostra->reg.ano);
        printf("\nsalario: %d", mostra->reg.salario);
        printf("\nsaldo: %d", mostra->reg.saldo);
        printf("\ncredito: %d", mostra->reg.credito);
        printf("\ndivida: %d", mostra->reg.divida);
        printf("\nconta: %d", mostra->reg.conta);
        printf("\nsenha: %d\n\n", mostra->reg.senha);
        mostra=mostra->prox;
   }
    printf("FIM\n\n");
}

void printMenu(void) {
	printf("Menu\n");
	printf("1 - Acessar sua conta\n");
    printf("---------------------------------\n");
	printf("2 - Criar sua conta\n");
    printf("---------------------------------\n");
	printf("3 - Proximo mes\n");
    printf("---------------------------------\n");
    printf("4 - Informacoes\n");
    printf("---------------------------------\n");
    printf("5 - fechar\n\n");
}

void info(void){
    int a;
    
    
    printf("Para informacoes sobre o funcionamento, digite 1.\n");
    printf("-------------------------------------------------\n");
    printf("Para informacoes sobre o programa, digite 2.\n");
    printf("-------------------------------------------------\n");
    printf("Para retornar, digite 0.\n\nOpcao:");
    scanf("%d", &a);
    while(1){    
        while(a!=1 && a!=2 && a!=0){
            printf("Invalido, tente novamente\nOpcoes validas: 1, 2, 3.\nOpcao:");
            scanf("%d", &a);
        }

        if(a==1){
            
            printf("\nNeste programa voce podera criar uma conta em um banco e administra-la. ");
            printf("Ao escolher a opcao de criar uma conta voce passara por um processo de coleta de dados necessarios para a criacao da sua conta, tudo bem intuivo. ");
            printf("Ao acessar a opcao de login voce sera levado \n");
            printf("\nOpcao:");
            scanf("%d", &a);
        }
        
        if(a==2){    
            printf("\nPrograma feito como trabalho final da materia de AED1 pelo curso de Ciencias da Computacao, UFG\nCriadores:Joao Paulo Lopes de Carvalho Grilo e Thales fossalussa\n11/2020\n\nOpcao:");
            scanf("%d", &a);
        }
        if(a==0) break;
    }
}