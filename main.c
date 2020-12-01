#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoes.h"

int main() {
    int select = 0;
    int fechar = 0;
    BANCO conta;
	printMenu(select);

	while(fechar == 0){
        switch(select) {
            case 1://acessa a conta
                printf("Foi escolhido o 1\n");
                select = 0;
                printMenu(select);
                break;
            case 2://cria uma conta
                inserirConta(&conta);
                select = 0;
                printMenu(select);
                break;
            case 3://passa o mês
                printf("Foi escolhido o 3\n");
                select = 0;
                printMenu(select);
                break;
            case 4://passa as informações do programa
                info();
                select = 0;
                printMenu(select);
                break;
            case 5://encerra o programa
                printf("Ate a proxima! :)\n");
                
                fechar = 1;
                break;
	    }
    }
	return 0;
}