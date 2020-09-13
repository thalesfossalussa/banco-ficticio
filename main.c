#include <stdio.h>

void printMenu(int * select) {

	printf("Menu\n");
	printf("1 - Gerar uma conta\n");
	printf("2 - Verificador de CPF\n");
	printf("3 - Gerar um RG\n");
	
	while(*select < 1 || *select > 3){
		scanf("%d", select);
	}
}

int main() {
	int select = 0;
	printMenu(&select);	

	switch(select) {
		case 1:
		printf("Foi escolhido o 1\n");
	break;
		case 2:
		printf("Foi escolhido o 2\n");
	break;
		case 3:
		printf("Foi escolhido o 3\n");
	break;
	}

	return 0;
}
