#include "App.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Cria uma instancia da aplicação
// Pré-condição: Nenhuma
// Pós-condição: Instancia valida da aplicação
App *createApp() {
    App *app = malloc(sizeof(App));
    app->tree = createTree();
    return app;
}

// Limpa buffer padrao de entrada
// Pré-condição: Nenhuma
// Pós-condição: Buffer de entrada limpo
static void aux_flushBuffer() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}

// Funçao auxiliar para ler uma linha do stdin dinamicamente
// Pré-condição: Nenhuma
// Pós-condição: Ponteiro para string dinamica contendo a linha inserida
static char* aux_readLine(FILE* input)
{
    char tmp[100], *str = NULL;
    int n, used = 0;
    while (1) {
        if (!fgets(tmp, sizeof(tmp), input))
            return str;

        n = strcspn(tmp,"\r\n");
        tmp[n] = '\0';

        str = realloc(str, sizeof(char) * (used + n + 1));
        memcpy(str + used,tmp, n + 1 );
        used += n;

        if (n + 1 < sizeof(tmp)) {
            break;
        }
    }
    return str;
}

// Requisita opcao ao usuário
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Opcao do app preenchida com opçao lida do usuário
int requestOption(App *app) {
    if (scanf("%u%*c", &app->option) != 1) {
        aux_flushBuffer();
        return 0;
    }
    return 1;
}

// Verifica se todos os caracteres da palavra são validos, padronizando quando necessário
// Pré-condição: nenhuma
// Pós-condição: Retorna 1 caso todos os caracteres da palavra sejam validos e 0 caso contrario, transforma
// todos carateres alfabeticos para o formato minusculo.
int isValidWord(char* str) {
    while(*str != '\0') {
        if (!isalpha(*str))
            return 0;
        *str = tolower(*str);
        str++;
    }
    return 1;
}

// Executa a opção presente no app
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Opcao executada caso encontrada
void executeOption(App *app) {
    char* buffer;
    int count = 0;
    FILE* file;

    switch (app->option) {
        case OP_INSERT: {
            file = requestFile();
            while((buffer = aux_readLine(file))) {
                if (isValidWord(buffer)) {
                    insert(app->tree, buffer);
                    printf("Palavra inserida: %s\n", buffer);
                    count++;
                } else {
                    printf("Palavra invalida: %s\n", buffer);
                }
                free(buffer);
            }
            printf("Foram adicionadas %d palavras ao dicionario\n", count);
        } break;
        case OP_REMOVE: {
            file = requestFile();
            while((buffer = aux_readLine(file))) {
                if (isValidWord(buffer)) {
                    if (removeOne(app->tree, buffer)) {
                        printf("Palavra removida: %s\n", buffer);
                        count++;
                    } else {
                        printf("Palavra nao encontrada: %s\n", buffer);
                    }
                } else {
                    printf("Palavra invalida: %s\n", buffer);
                }
                free(buffer);
            }
            printf("Foram removidas %d palavras do dicionario\n", count);
        } break;
        case OP_SEARCH: {
            printf("Digite a palavra a ser consultada: ");
            char *str = aux_readLine(stdin);
            printContainOcorrences(app->tree, str);
        } break;
        case OP_PRINT_ASC:
            printAsc(app->tree);
            break;
        case OP_EXIT:
            break;
    }
}

// Inicia o loop do programa
// Pré-condição: Ponteiro para instancia valida do app
// Pós-condição: Nenhuma
void startApp(App *app) {
    do {
        printMenu();
        if (!requestOption(app))
            continue;
        executeOption(app);
    } while (app->option != OP_EXIT);
}

// Requisita um caminho para arquivo e o abre
// Pré-condição: Nenhuma
// Pós-condição: Ponteiro para arquivo aberto em modo de leitura
FILE* requestFile() {
    printf("Insira o arquivo:");
    FILE* file;
    while (1) {
        char *fileName = aux_readLine(stdin);
        file = fopen(fileName, "r");
        free(fileName);

        if (file == NULL)
            printf("Arquivo nao encontrado, insira outro arquivo:");
        else
            break;
    }
    return file;
}

// Imprime o menu com as opçoes disponiveis
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
void printMenu() {
    printf("\n1 - Carregar palavras\n");
    printf("2 - Carregar arquivo de stopword\n");
    printf("3 - Consultar palavra\n");
    printf("4 - Imprimir dicionario\n");
    printf("5 - Sair\n\n");
    printf("Insira o numero da opcao desejada: ");
}