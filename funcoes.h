#ifndef FUNCOES_H
#define FUNCOES_H

// struct que abriga os dados da conta/registro do cliente
typedef struct
{
    char nome[200];
    int cpf;
    int cpfd;
    int dia;
    int mes;
    int ano;
    float salario;
    float saldo;
    float despesas;
    float credito;
    float fatura;
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

/* Insere uma conta no BANCO
 * l: Lista do banco
 */
void inserirConta(BANCO *l);

/* Exclui uma conta do BANCO
 * l: Lista do banco
 * conta: Número da conta que será excluída
 */
void excluirConta(BANCO *l, int conta);

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

/* Realiza o deposito
 * l: Lista do banco
 * nconta: número da conta em que será depositado
 * valor: valor que será depositado em conta
 */
void deposito(BANCO *l, int nconta , float valor);

// Função que deposita o salario para todas as contas do banco
void depositarSalario(BANCO *l);

#endif