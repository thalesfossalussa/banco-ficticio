#include <stdio.h>
#include <stdlib.h>

void printMenu(int * select) {

	printf("Menu\n");
	printf("1 - Gerar um cartão\n");
	printf("2 - Verificador de CPF\n");
	printf("3 - Gerar um RG\n");
	
	while(*select < 1 || *select > 3){
		scanf("%d", select);
	}
}

int verifica_cpf(int *cpf){
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
}

int main() {
	int select = 0;
	printMenu(&select);	

	switch(select) {
		case 1:
			printf("Foi escolhido o 1\n");
	break;
		case 2:
			verifica();
	break;
		case 3:
			printf("Foi escolhido o 3\n");
	break;
	}

	return 0;
}
