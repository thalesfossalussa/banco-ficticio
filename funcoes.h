#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    char nome[30];
    int cpf;
    int dia;
    int mes;
    int ano;
    int salario;
    int saldo;
    int credito;
    int divida;
    int conta;
    int senha;
} REGISTRO; //struct que abriga os dados da conta/registro do cliente
    
typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO; 

typedef ELEMENTO* PONT;

typedef struct {
    PONT inicio;
} BANCO;

void inicializarBanco(BANCO* l);

int tamanhoBanco(BANCO* l);

PONT buscarConta(BANCO* l, int cpf, PONT* ant);

void inserirConta(BANCO* l);

void excluirConta(BANCO* l, int cpf);

void operacoes(PONT* l);

void login(BANCO* l);

void info(void);

#endif