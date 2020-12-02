#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes.h"

int main() {
    int select = 0;
    int fechar = 0;
    BANCO contas;
    inicializarBanco(&contas);
	
    while(fechar == 0){
        printMenu();
        scanf("%d", &select);
        switch(select) {
            case 1://acessa a conta
                login(&contas);
                select = 0;
                break;
            case 2:
                inserirConta(&contas);
                select = 0;
                break;
            case 3://passa o mês
                printf("Foi escolhido o 3\n");
                select = 0;
                break;
            case 4://passa as informações do programa
                info();
                select = 0;
                break;
            case 5://encerra o programa
                printf("\nAte a proxima! :)\n");
                fechar = 1;
                break;
            default:
                printf("Valor inválido, tente novamente\n\n");
                break;
	    }
    }
	return 0;
}