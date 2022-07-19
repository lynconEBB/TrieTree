#ifndef TRIETREE_APP_H
#define TRIETREE_APP_H
#include <stdio.h>
#include "TreeTrie.h"

// Enum apresentando as opções disponiveis pare serem executadas pela aplicação
typedef enum {
    OP_INSERT = 1,
    OP_REMOVE = 2,
    OP_SEARCH = 3,
    OP_PRINT_ASC = 4,
    OP_EXIT = 5
} Option;

// Estrutura representando os componentes da aplicação
typedef struct {
    Option option; // Opção lida
    TreeTrie* tree;
} App;

// Imprime o menu com as opçoes disponiveis
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
void printMenu();

// Cria uma instancia da aplicação
// Pré-condição: Nenhuma
// Pós-condição: Instancia valida da aplicação
App* createApp();

// Inicia o loop do programa
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Nenhuma
void startApp(App* app);

// Executa a opção presente no app
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Opcao executada caso encontrada
void executeOption(App* app);

// Verifica se todos os caracteres da palavra são validos, padronizando quando necessário
// Pré-condição: nenhuma
// Pós-condição: Retorna 1 caso todos os caracteres da palavra sejam validos e 0 caso contrario, transforma
// todos carateres alfabeticos para o formato minusculo.
int isValidWord(char* str);

// Requisita opcao ao usuário
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Opcao do app preenchida com opçao lida do usuário
int requestOption(App* app);

// Requisita um caminho para arquivo e o abre
// Pré-condição: Nenhuma
// Pós-condição: Ponteiro para arquivo aberto em modo de leitura
FILE* requestFile();

#endif