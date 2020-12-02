#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int select = 0;
    int fechar = 0;
    int mes=12, ano=2020;
    BANCO conta;
	inicializarBanco(&conta);
    
    while(fechar == 0){
        if(mes>12){
            mes=mes-12;
            ano++;
        }
        printf("\nData: %d/%d\n", mes, ano);
        printMenu();
        printf("Opcao:");
        scanf("%d", &select);
        printf("\n");
        switch(select) {
            case 1://acessa a conta
                login(&conta);
                select = 0;
                break;
            case 2://cria uma conta
                inserirConta(&conta);
                select = 0;
                break;
            case 3://passa o mês e deposita os salários nas contas
                deposito(&conta);
                mes++;
                select = 0;
                break;
            case 4://passa as informações do programa
                info();
                select = 0;
                break;
            case 5://encerra o programa
                limpa(&conta);
                printf("Ate a proxima! :)\n");
                fechar = 1;
                break;
            case 6:
                imprime(&conta);
                select = 0;
                break;
            default:
                printf("Valor inválido, tente novamente\n\n");
                break;
	    }
    }
	return 0;
}