#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "funcoes.h"

void inicializarBanco(BANCO *l)
{
    l->inicio = NULL;
}

int tamanhoBanco(BANCO *l)
{
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
}

void inserirConta(BANCO *l)
{
    PONT i, ant;
    int tam, senha1, senha2, c = 0;
    float cpf;
    tam = tamanhoBanco(l);
    ant = l->inicio;

    i = (PONT)malloc(sizeof(ELEMENTO)); //aloca nova conta

    if (tam == 0)
    { //caso a lista esteja vazia faz com que o começo seja a nova conta e aponta o prox como null
        l->inicio = i;
        i->prox = NULL;
    }
    else
    {
        while (ant->prox != NULL)
            ant = ant->prox; //acha o ultimo elemento da lista que aponta para NULL
        ant->prox = i;       //faz com que o antigo ultimo elemento aponte para a nova conta, que se torna o novo ultimo elemento
        i->prox = NULL;
    } //processo de alocação de memória feito, agora para o preenchimento de dados

    printf("-------------------------------------------------------------------------------\n");
    printf("Ok, para comecarmos nos diga o seu nome:\n");
    while (1)
    {
        scanf("%s", i->reg.nome);
        printf("Senhor(a) %s?\nCaso tenha errado, basta digitar o nome correto, caso esteja correto, digite 1:\nOpcao:", i->reg.nome);
        scanf("%d", &c);
        if (c == 0)
            printf("Nome: ");
        if (c == 1)
            break;
    }

    printf("\nSeu CPF no seguinte formato ********* **\nCPF:");
    scanf("%d %d", &i->reg.cpf, &i->reg.cpfd);
    while (i->reg.cpf > 999999999 || i->reg.cpf < 100000000 || i->reg.cpfd>99 || i->reg.cpfd<1)
    { //caso o cpf tenha menos de 9 dígitos e o digito tenha menos de 2 dígitos ele não será aceito, funciona já que não há cpf que comece com 0
        printf("\n==========================================\n");
        printf("CPF invalido! Por favor, insira novamente.\n");
        printf("==========================================\nCPF:");
        scanf("%d %d", &i->reg.cpf, &i->reg.cpfd);
    }
    printf("\nSua data de nascimento no seguinte formato dd mm aaaa:");
    scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    while (i->reg.dia < 1 || i->reg.dia > 31 || i->reg.mes < 1 || i->reg.mes > 12 || i->reg.ano > 2002)
    { //não fiz casos especiais para ano bisexto e essas paradas, se quiser dar uma olhada nisso fique a vontade, da pra colocar uns if's no while tranquilamente
        printf("\n==========================================================\n");
        printf("Data de nascimento invalida! Por favor, insira novamente.\n");
        printf("==========================================================\n");
        scanf("%d %d %d", &i->reg.dia, &i->reg.mes, &i->reg.ano);
    }

    i->reg.conta = i->reg.cpf * i->reg.ano; //gerando o número de conta com 5 dígitos
    while (i->reg.conta > 99999)
        i->reg.conta = i->reg.conta / 10; //reduzindo-o aos 5 dígitos

    printf("\nSalario mensal R$");
    scanf("%f", &i->reg.salario);
    
    printf("\nDespesa mensal R$");
    scanf("%f", &i->reg.despesas);
    
    i->reg.saldo = i->reg.salario-i->reg.despesas;
    i->reg.credito = i->reg.salario * 0.2;
    i->reg.fatura = 0;

    printf("\nOk, %s, agora para algumas informacoes sobre sua conta.\nSeu numero de conta e >%d<.\n\nAgora digite uma senha de 4 digitos: ", i->reg.nome, i->reg.conta);
    scanf("%d", &senha1);
    while (1)
    {
        while (senha1 > 9999 || senha1 < 1000)
        {
            printf("Senha invalida! Tente, novamente.\nNova senha:");
            scanf("%d", &senha1);
        }
        printf("\nConfirme sua senha: ");
        scanf("%d", &senha2);
        if (senha2 == 0)
        {
            printf("Nova senha:");
            scanf("%d", &senha1);
            while (senha1 > 9999 || senha1 < 1000)
            {
                printf("Senha invalida! Tente, novamente.\nNova senha:");
                scanf("%d", &senha1);
            }
        }
        else
        {
            if (senha1 == senha2)
            {
                i->reg.senha = senha1;
                break;
            }
            else
            {
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

void excluirConta(BANCO *l, int conta)
{ //busca a conta do titular para exlui-la
    PONT ant, atual;
    atual = l->inicio;
    ant = NULL;
    while (atual->reg.conta != conta)
    {                        //caso as contas não batam o laço continua
        ant = atual;         //o anterior se torna o atual
        atual = atual->prox; //o atual se torna o próximo
    }
    if (ant == NULL)
        l->inicio = l->inicio->prox; //caso o anterior seja NULL, o atual já é o primeiro, logo só informamos que a lista começa a partir do segundo elemento
    else
        ant->prox = atual->prox; //caso o anterior não seja null, informamos que o próximo dele será o próximo do próximo, pulando uma posição que será exluída
    free(atual);                 //excluíndo posição
}

void transferencia(BANCO *l, float transferido)
{
    int ctrans;
    PONT cont = l->inicio;
    printf("Digite o numero da conta a receber a transferencia.\n");
    scanf("%d", &ctrans);
    while (cont != NULL)
    {
        if (ctrans == cont->reg.conta)
        {
            cont->reg.saldo += transferido;
            break;
        } else
            cont = cont->prox;
    }
    if (cont == NULL)
        printf("Conta inexistente!\n");
}

void menuOperacoes()
{
    printf("\n-----------------------------------------------------------\n");
    printf("O que deseja fazer?\n");
    printf("1 - Visualizar saldo.\n");
    printf("2 - Realizar um pagamento.\n");
    printf("3 - Sacar.\n");
    printf("4 - Depositar.\n");
    printf("5 - Realizar transferencia.\n");
    printf("6 - Consultar limite.\n");
    printf("7 - Consultar fatura.\n");
    printf("8 - Pagamento com credito.\n");
    printf("9 - Pagar fatura.\n");
    printf("10 - Alterar despesas mensais.\n");
    printf("11 - Encerrrar conta.\n");
    printf("0 - Sair.\n");
    printf("-----------------------------------------------------------\n");
    printf("Opcao: ");
}

void operacoes(BANCO *l, int nconta)
{
    int fechar = 0, a = 0, excluir;
    int cpf, cpfd, senha;
    float pagamento;
    PONT conta = l->inicio;
    while (conta->prox != NULL)
    {
        if (conta->reg.conta == nconta)
            break;
        conta = conta->prox;
    }
    while (fechar == 0)
    {
        menuOperacoes();
        scanf("%d", &a);
        switch (a)
        {
        case 1:
            printf("Seu saldo e de R$%.2f\n", conta->reg.saldo);
            break;

        case 2:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            printf("Voce tem R$%.2f disponiveis\nValor do pagamento: ", conta->reg.saldo);
            scanf("%f", &pagamento);
            printf("\n");
            if (pagamento > conta->reg.saldo)
                printf("Saldo insuficiente!\n");
            else
            {
                conta->reg.saldo = (conta->reg.saldo) - pagamento;
                printf("\nSeu novo saldo e de R$%.2f\n", conta->reg.saldo);
            }
            break;

        case 3:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            printf("Voce tem R$%.2f disponiveis\nValor do saque: ", conta->reg.saldo);
            scanf("%f", &pagamento);
            printf("\n");
            if (pagamento > conta->reg.saldo)
            {
                printf("Saldo insuficiente!\n");
                break ;
            }
            else
            {
                conta->reg.saldo = (conta->reg.saldo) - pagamento;
                printf("\nSeu novo saldo e de R$%.2f\n", conta->reg.saldo);
            }
            break;
        
        case 4:
            printf("Valor a ser depositado: R$");
            scanf("%f", &pagamento);
            deposito(l, conta->reg.conta, pagamento);
            break;

        case 5:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            printf("Voce tem R$%.2f disponiveis\nValor a ser transferido R$", conta->reg.saldo);
            scanf("%f", &pagamento);
            printf("\n");
            if (pagamento > conta->reg.saldo)
                printf("Saldo insuficiente!\n");
            else
            {
                conta->reg.saldo = conta->reg.saldo - pagamento;
                transferencia(l, pagamento);
            }

            break;

        case 6:
            printf("Seu limite e de R$%.2f\n", conta->reg.credito);
            break;

        case 7:
            printf("O valor da fatura e de R$%.2f\n", conta->reg.fatura);
            break;
        case 8:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            printf("Voce tem R$%.2f de credito disponivel\nValor do pagamento: ", conta->reg.credito - conta->reg.fatura);
            scanf("%f", &pagamento);
            printf("\n");
            if ((conta->reg.fatura + pagamento) > conta->reg.credito)
                printf("Credito insuficiente!\n");
            else
            {
                conta->reg.fatura = (conta->reg.fatura) + pagamento;
                printf("\nValor da conta descontando o credito disponivel R$%.2f.", conta->reg.credito - conta->reg.fatura);
            }
            break;

        case 9:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n(Para mais informacoes, acesse o opcao *info* no menu inicial.)\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            printf("Voce tem um total de R$%.2f de credito a ser pago.\nDeseja pagar? (1 para sim | 0 para não)\n", conta->reg.fatura);
            scanf("%f", &pagamento);
            if (pagamento == 0)
                break;
            if (pagamento == 1)
            {
                if (conta->reg.fatura > conta->reg.saldo)
                    printf("Saldo insuficiente!\n");
                else
                {
                    conta->reg.saldo = conta->reg.saldo - conta->reg.fatura;
                    conta->reg.fatura = 0.00;
                    printf("Pagamento feito com sucesso!\nNovo saldo disponivel R$%.2f.\n", conta->reg.saldo);
                }
            }
            break;

        case 10:
            printf("Insira o valor da nova despesa mensal.\nR$:");
            scanf("%f", &conta->reg.despesas);
            while(conta->reg.despesas>conta->reg.salario){
                printf("\n=====================================================\n");
                printf("Despesa mensal maior que o salario, insira novamente!\n");
                printf("=====================================================\n");
                printf("Insira o valor da nova despesa mensal.\nR$:");
                scanf("%f", &conta->reg.despesas);
            }

            break;


        case 11:
            if(conta->reg.saldo < 0){
                printf("\n==============================================================================================\n");
                printf("Sua conta esta bloqueada para esse tipo de operacao ate que seja paga a divida gerada de R$%.2f\n(Para mais informacoes, acesse o opcao *info* no menu inicial.)\n", conta->reg.salario*-1);
                printf("==============================================================================================\n");
                break;
            }
            
            while (cpf != conta->reg.cpf || cpfd!=conta->reg.cpfd || senha != conta->reg.senha)
            {
                printf("\n\nCerto, primeiro precisamos que voce confirme seu cpf no formato ********* **\nCPF:");
                scanf("%d", &cpf);
                scanf("%d", &cpfd);
                printf("\nAgora digite sua senha:");
                scanf("%d &d", &senha);

                if (cpf != conta->reg.cpf || cpfd!=conta->reg.cpfd || senha != conta->reg.senha)
                {
                    printf("Dados incorretos, deseja tentar novamente?\n(1 para sim, 0 para nao).\nOpcao: ");
                    scanf("%d", &excluir);
                    printf("\n");
                    if (excluir == 0)
                        break;
                }
                else
                {
                    excluirConta(l, conta->reg.conta);
                    printf("Obrigado pelo seu tempo conosco, ate uma proxima.\n");
                    return;
                }
            }
            break;

        case 0:
            printf("Obrigado, volte sempre.\n");
            return;
            break;
        default:
            printf("Operacao invalida, tente novamente.\n");
            break;
        }
    }
}

void login(BANCO *l)
{ //busca pelo banco uma conta que tenha o nconta e senha iguais aos informados
    int nconta, senha, v = 0;
    PONT conta;
    if (l->inicio == NULL)
    {
        printf("Ainda nao possuimos contas cadastradas, crie sua conta agora escolhendo a opcao 2\n");
        return;
    }
    conta = l->inicio;
    printf("Digite seu numero de conta:");
    scanf("%d", &nconta);
    printf("\nDigite sua senha:");
    scanf("%d", &senha);
    while (1)
    { //percorre as structs
        if ((nconta == conta->reg.conta) && (senha == conta->reg.senha))
        { //caso onde as informações batem
            v++;
            break;
        }
        else if (conta->prox != NULL)
            conta = conta->prox;
        else
            break;
    }
    if (v > 0)
    {
        printf("\nSeja bem vindo(a), %s!\n", conta->reg.nome);
        operacoes(l, conta->reg.conta);
    }
    else
    {
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("Numero de conta ou senha incorretos ou inexistentes, voltando ao menu.\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
    }
}

void deposito(BANCO *l, int nconta , float valor)
{
    PONT conta = l->inicio;
    while (conta != NULL)
    {
        if(conta->reg.conta == nconta)
            break;
        else
            conta = conta->prox;
    }
    if (conta == NULL)
        printf("\nConta inexistente, consulte o administrador do sistema!");
    else
    {
        conta->reg.saldo += valor;
        printf("\nValor depositado na conta, novo saldo e R$%.2f\n", conta->reg.saldo);
    }
    return;
}

void depositarSalario(BANCO *l)
{
    PONT conta = l->inicio;
    while (conta!= NULL)
    {
        conta->reg.saldo = conta->reg.saldo + conta->reg.salario - conta->reg.despesas;
        conta->reg.fatura=conta->reg.fatura*1.05;
        if(conta->reg.fatura>conta->reg.credito){
            conta->reg.saldo=conta->reg.saldo-conta->reg.fatura;
            conta->reg.fatura=0;
        }
        conta = conta->prox;
    }
}

void limpa(BANCO *l)
{
    PONT end = l->inicio;
    while (end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
}

void informacoesConta(BANCO *l)
{
    PONT mostra = l->inicio;
    while (mostra != NULL)
    {
        printf("cpf: %d", mostra->reg.cpf);
        printf("\ndigito: %d", mostra->reg.cpfd);
        printf("\nnome: %s", mostra->reg.nome);
        printf("\ndata: %d/%d/%d", mostra->reg.dia, mostra->reg.mes, mostra->reg.ano);
        printf("\nsalario: %.2f", mostra->reg.salario);
        printf("\ndespesas: %.2f", mostra->reg.despesas);
        printf("\nsaldo: %.2f", mostra->reg.saldo);
        printf("\ncredito: %.2f", mostra->reg.credito);
        printf("\ndivida: %.2f", mostra->reg.fatura);
        printf("\nconta: %d", mostra->reg.conta);
        printf("\nsenha: %d\n\n", mostra->reg.senha);
        mostra = mostra->prox;
    }
    printf("FIM\n\n");
}

void printMenu(void)
{
    printf("===============Menu==============\n\n");
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

void info(void)
{
    int a;

    while (1)
    {
        printf("Para informacoes sobre o funcionamento, digite 1.\n");
        printf("--------------------------------------------------------\n");
        printf("Para informacoes sobre o programa, digite 2.\n");
        printf("-------------------------------------------------------\n");
        printf("Para informacoes sobre os descontos no saldo, digite 3.\n");
        printf("-------------------------------------------------------\n");
        printf("Para retornar, digite 0.\n\nOpcao:");
        scanf("%d", &a);

        while (a != 1 && a != 2 && a!=3 && a != 0)
        {
            printf("Invalido, tente novamente\nOpcoes validas: 1, 2, 3 e 0 para sair.\n\n");
        }

        if (a == 1)
        {

            printf("\nNeste programa voce podera criar uma conta em um banco e administra-la. ");
            printf("Ao escolher a opcao de criar uma conta voce passara por um processo de coleta de dados necessarios para a criacao da sua conta, tudo bem intuivo. ");
            printf("Ao acessar a opcao de login voce sera levado podera acessar a sua conta e realizar diversas operacoes la listadas.\n\n");
        }

        if (a == 2)
        {
            printf("\nPrograma feito como trabalho final da materia de AED1 pelo curso de Ciencias da Computacao, UFG\nCriadores:Joao Paulo Lopes de Carvalho Grilo e Thales fossalussa\n11/2020\n\n");
        }
        
        if(a == 3){
            printf("\nExistem dois descontos automaticos que podem ser aplicados no saldo da conta, o das despesas mensais e a fatura do credito gasto quando o limite de credito e ultrapassado.\n");
            printf("A cada mes que se passa e aplicado um juro de 5% sobre o credito ja gasto.\n");
            printf("Caso a soma das despesas e da fatura de credito descontada seja superior ao saldo disponivel na conta, ela sera negativada e impedida de realizar operacoes que gastariam debito ou credito ate que a situacao seja normalizada ou o encerramento da conta.\n\n");
        }
        if (a == 0)
            break;
    }
}