#ifndef FUNCOES_H
#define FUNCOES_H

// struct que abriga os dados da conta/registro do cliente
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
} REGISTRO;

// struct que guarda o registro e aponta para o prox   
typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO; 

// Criando ponteiro para ELEMENTO
typedef ELEMENTO* PONT;

// Criando struct BANCO para guardar o inicio da lista
typedef struct {
    PONT inicio;
} BANCO;

// Inicialiazndo lista
void inicializarBanco(BANCO* l);

// Retorna o tamanho do BANCO
int tamanhoBanco(BANCO* l);

// Busca uma conta no banco
PONT buscarConta(BANCO* l, int cpf, PONT* ant);

// Insere uma conta no BANCO
void inserirConta(BANCO* l);

// Exclui uma conta do BANCO
void excluirConta(BANCO* l, int cpf);

// Menu para operações bancárias
void operacoes(PONT* l);

// Login com a conta
void login(BANCO* l);

// Mostra as informações do programa
void info(void);

#endif