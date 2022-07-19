#include "TreeTrie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Cria um nó de árvore Trie vazio
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
TstNode *createNode() {
    TstNode* node = malloc(sizeof(TstNode));
    node->minor = NULL;
    node->greater = NULL;
    node->equal = NULL;
    node->chr = '\0';
    node->isFinal = 0;
    return node;
}

// Cria uma árvore Trie vazia
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
TreeTrie *createTree() {
    TreeTrie* tree = malloc(sizeof(TreeTrie));
    tree->root = NULL;
    tree->maxSize = 0;
    return tree;
}

// Função auxiliar recursiva para criar nós segundo uma palavra
// Pré-condição: Nenhuma
// Pós-condição: Nós criados quando necessário
TstNode* aux_insert(TstNode* node, char* str) {
    if (*str == '\0')
        return NULL;
    if (node == NULL) {
        node = createNode();
        node->chr = *str;
    }

    if (*str == node->chr) {
        if (*(str + 1) != '\0')
            node->equal = aux_insert(node->equal, str + 1);
        else
            node->isFinal = 1;
    } else {
        if (*str < node->chr)
            node->minor = aux_insert(node->minor, str);
        else
            node->greater = aux_insert(node->greater, str);
    }

    return node;
}

// Insere uma nova palavra na árvore fornecida
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Palavra inserida na árvore criando os nós necessários
void insert(TreeTrie *tree, char *word) {
    tree->root = aux_insert(tree->root, word);
    if (strlen(word) > tree->maxSize) {
        tree->maxSize = strlen(word);
    }
}

// Função auxiliar recursiva para imprimir as palavras presentes na árvore Trie
// Pré-condição: Nenhuma
// Pós-condição: Caso um numero positivo seja passado como limite apenas esse número de palavras será
// exibido, caso 'commaSeparated' seja 1, as palavras serão impressas separadas por virgula, caso
// contrario, serão impressas por linha
void aux_printAsc(TstNode* node, char* prefix, int* limit, int commaSeparated) {
    if (node == NULL)
        return;

    unsigned int length = strlen(prefix);
    aux_printAsc(node->minor, prefix, limit, commaSeparated);

    prefix[length + 1] = '\0';
    prefix[length] = node->chr;

    if (node->isFinal) {
        if (*limit == 0 )
            return;
        if (*limit > 0)
            *limit = (*limit) - 1;
        if (commaSeparated)
            printf("%s, ", prefix);
        else
            printf("%s\n",prefix);
    }

    aux_printAsc(node->equal, prefix, limit, commaSeparated);

    prefix[length] = '\0';
    aux_printAsc(node->greater, prefix, limit, commaSeparated);
}

// Imprime todas as palavras da árvore em ordem alfabetica
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Nenhuma
void printAsc(TreeTrie *tree) {
    char prefix[tree->maxSize];
    prefix[0] = '\0';
    if (tree->root == NULL) {
        printf("Nenhuma palavra cadastrada!\n");
        return;
    }
    int limit = -1;
    aux_printAsc(tree->root, prefix, &limit, 0);
}
// Encontra nó contendo o final da palavra fornecida
// Pré-condição: Ponteiro para árvore Trie válida
// Pós-condição: Retorna um ponteiro para o nó final da palavra ou NULL caso a palavra não seja encotnrada
TstNode* search(TstNode* node, char* word) {
    if (node == NULL)
        return NULL;

    if (node->chr == *word) {
        if (*(word + 1) == '\0')
            return node;
        else
            return search(node->equal,word + 1);
    } else if (*word < node->chr)
        return search(node->minor, word);
    else
        return search(node->greater, word);
}

// Imprime no máximo 10 palavras da árvore que contenham a palavra fornecida como prefixo
// Pré-condição: Ponteiro para árvore Trie válida
// Pós-condição: Nenhuma
void printContainOcorrences(TreeTrie *tree, char* word) {
    if (*word == '\0')
        return;

    TstNode* findNode = search(tree->root, word);
    if (findNode == NULL) {
        printf("Nenhuma palavra encontrada!");
        return;
    }

    int limit = 10;
    if (findNode->isFinal) {
        printf("%s",word);
        limit--;
    }
    char prefix[tree->maxSize];
    strcpy(prefix, word);
    aux_printAsc(findNode->equal, prefix, &limit, 1);
    printf("\b\b \n");
}

// Função auxiliar recursiva para remover os nós necessários caso a palavra seja encontrada
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Nó removido caso não tenha filhos, não seja palavra final e a palavra tenha sido encontrada
TstNode* aux_remove(TstNode* node, char* str, int* findFlag) {
    if (node == NULL || *str == '\0') {
        *findFlag = 0;
        return node;
    }

    if (*str == node->chr) {
        if (*(str+1) != '\0') {
            node->equal = aux_remove(node->equal, str+1, findFlag);
        } else if (node->isFinal){
            node->isFinal = 0;
            *findFlag = 1;
        }
    } else if (*str > node->chr) {
        node->greater = aux_remove(node->greater, str, findFlag);
    } else {
        node->minor = aux_remove(node->minor, str, findFlag);
    }

    if (node->minor == NULL && node->greater == NULL && node->equal == NULL && !node->isFinal && *findFlag) {
        free(node);
        node = NULL;
    }

    return node;
}

// Remove uma palavra da árvore Trie fornecida
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Caso a palavra seja encontrada, 1 é retornada e os nós desncessários são removidos,
// caso contrario, 0 é retornado
int removeOne(TreeTrie *tree, char *word) {
    int findFlag = 0;
    tree->root = aux_remove(tree->root, word, &findFlag);
    return findFlag;
}
