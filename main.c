#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "funcoes.h"

int main()
{
    int select = 0;
    int fechar = 0;
    int mes = 11, ano = 2020;
    BANCO contas;
    inicializarBanco(&contas);

    while (fechar == 0)
    {
        if (mes > 12)
        {
            mes = mes - 12;
            ano++;
        }
        printf("\nData: %d/%d\n", mes, ano);
        printMenu();
        printf("Opcao:");
        scanf("%d", &select);
        printf("\n");
        switch (select)
        {
        case 1: //acessa a conta
            login(&contas);
            select = 0;
            break;
        case 2:
            inserirConta(&contas);
            select = 0;
            break;
        case 3: //passa o mês e deposita os salários nas contas
            depositarSalario(&contas);
            mes++;
            select = 0;
            break;
        case 4: //passa as informações do programa
            info();
            select = 0;
            break;
        case 5: //encerra o programa
            limpa(&contas);
            printf("Ate a proxima! :\n");
            fechar = 1;
            break;
        case 6:
            informacoesConta(&contas);
            select = 0;
            break;
        default:
            printf("Valor inválido, tente novamente\n\n");
            break;
        }
    }
    return 0;
}