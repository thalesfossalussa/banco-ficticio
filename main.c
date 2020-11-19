#include <stdio.h>
#include <stdlib.h>

void info(){
    printf("\n\n\n\nPrograma feito como trabalho final da materia de AED1 pelo curso de Ciencias da Computacao, UFG\nCriadores:Joao Paulo Lopes de Carvalho Grilo e Thales fossalussa\n11/2020\n\n\n\n");
}

void printMenu(int * select) {

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
	
	while(*select < 1 || *select > 5){
		scanf("%d", select);
	}
}

void criar_conta(int * select){
    int cpf, dd, mm, aaaa, sal, conta, senha1, senha2, cred, c=0;

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Que otimo que decidiu se juntar a nos. Por favor, informe-nos dos seus seguintes dados:\n\n");
    printf("CPF:\n");
    scanf("%d", &cpf);
    while(!cpf>9999999999){
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("|CPF invalido! Por favor, insira novamente.|\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        scanf("%d", &cpf);
    }
    printf("Data de nascimento no seguinte formato dd/mm/aaaa:\n");
    scanf("%d %d %d", &dd, &mm, &aaaa);
    while(!dd>0 && !dd<31 && !mm>0 && !mm<12 && !aaaa>2012){
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        printf("|Data de nasciemento invalida! Por favor, insira novamente.|\n");
        printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
        scanf("%d %d %d", &dd, &mm, &aaaa);
    }
    conta=cpf*aaaa/1000000000;
    printf("Media salarial:\n");
    scanf("&d", &sal);

    printf("Ok, agora para algumas informacoes sobre sua conta.\nSeu numero de conta e >%d<\nPor favor, Crie uma senha de 4 digitos:\n",conta);
    scanf("%d", &senha1);
    while(1){
        printf("Confirme sua senha:\n");
        scanf("%d", &senha2);
        if(senha2==0) {
            printf("Nova senha:\n");
            scanf("%d", &senha1);
        }
        else{
            if(senha1==senha2) break;
            else{
                printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
                printf("|As senhas não batem. Tente novamente ou digite *0* para recriar a senha.|\n");
                printf("|!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!|\n");
            }
        }
    }
    printf("Confirmado!\n\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|Seja bem vindo ao banco Pequi, para mais informacoes, acessar a opcao *info* no menu inicial. O banco Pequi agradece sua escolha|\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------|\n\n\n");

    select=0;
	printMenu(select);	

    

}

/*int verifica_cpf(int *cpf){
    int c, k=10, d1=0, d2=0;
    
    for(c=0;c<9;c++){
        d1=d1+cpf[c]*k;
        k--;
    }
    d1=(d1*10)%11;
    k=11;
    if(d1==cpf[9]){
        for(c=0;c<10;c++){
            d2=d2+cpf[c]*k;
            k--;
        }
        d2=(d2*10)%11;
        if(d2==cpf[10]){
            printf("cpf valido\n");
            return 1;
        } else {
            printf("cpf invalido\n");
            return 0;
        }
    } else {
        printf("cpf invalido\n");
        return 0;
    }
}

int verifica(){
    int c;
    int *cpf;

    cpf=(int*)calloc(11,sizeof(int));
    
    for(c=0;c<11;c++){
        scanf("%d", &cpf[c]);
    }

    verifica_cpf(cpf);
    
    free(cpf);
    
    return 0;
}*/

int main() {
	int select = 0;
	printMenu(&select);	

	while(1){
        switch(select) {
            case 1://acessa a conta
                printf("Foi escolhido o 1\n");
                select = 0;
                printMenu(&select);
        break;
            case 2://cria uma conta
                criar_conta(&select);
                select = 0;
                printMenu(&select);
        break;
            case 3://passa o mês
                printf("Foi escolhido o 3\n");
                select = 0;
                printMenu(&select);
        break;
            case 4://passa as informações do programa
                info();
                select = 0;
                printMenu(&select);
        break;
            case 5://encerra o programa
                printf("Ate a proxima! :)\n");
                
                return 0;
        break;
	    }
    }

	return 0;
}