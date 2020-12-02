#ifndef FUNCOES_H
#define FUNCOES_H

// struct que abriga os dados da conta/registro do cliente
typedef struct
{
    char nome[30];
    long int cpf;
    int dia;
    int mes;
    int ano;
    float salario;
    float saldo;
    float credito;
    float divida;
    int conta;
    int senha;
} REGISTRO;

// struct que guarda o registro e aponta para o prox
typedef struct aux
{
    REGISTRO reg;
    struct aux *prox;
} ELEMENTO;

// Criando ponteiro para ELEMENTO
typedef ELEMENTO *PONT;

// Criando struct BANCO para guardar o inicio da lista
typedef struct
{
    PONT inicio;
} BANCO;

/* Inicializando banco
 * l:Lista onde será armazenado o banco
 */
void inicializarBanco(BANCO *l);

/* Retorna o tamanho do BANCO
 * l: Lista que deseja-se extrair o tamanho
 */
int tamanhoBanco(BANCO *l);

/* Busca uma conta no BANCO
 * l: lista de contas
 * cpf: cpf que será buscado
 */
PONT buscarConta(BANCO *l, long int cpf);

/* Insere uma conta no BANCO
 * l: Lista do banco
 */
void inserirConta(BANCO *l);

/* Exclui uma conta do BANCO
 * l: Lista do banco
 * cpf: cpf do portador da conta que será excluída
 */
void excluirConta(BANCO *l, long int cpf);

// Printa o menu de operações
void menuOperacoes(void);

/* Operações da conta
 * l: Lista do banco
 * nconta: número da conta que será operada
 */
void operacoes(BANCO *l, int nconta);

/* Transferencia entre contas
 * l: Lista do banco
 * transferido: valor a ser trasnferido
 */
void transferencia(BANCO *l, float transferido);

/* Efetuar login no banco
 * l: Lista do banco
 */
void login(BANCO *l);

/* Realiza o deposito
 * l: Lista do banco
 */
void deposito(BANCO *l);

/* Realiza uma limpeza na lista BANCO
 * l: lista do banco
 */
void limpa(BANCO *l);

/* Mostra as informações da conta do usuário
 * l: Lista do banco
 */
void informacoesConta(BANCO *l);

// Printa o menu inicial
void printMenu(void);

// Mostra as informações do programa
void info(void);

#endif