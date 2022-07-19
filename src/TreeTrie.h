#ifndef TRIETREE_TREETRIE_H
#define TRIETREE_TREETRIE_H

// Estrutura para representar um nó de árvore Trie no formato TST
typedef struct TstNode {
    char chr;
    int isFinal;
    struct TstNode *minor;
    struct TstNode *equal;
    struct TstNode *greater;
} TstNode;

// Estrutura para representar uma árvore Trie
typedef struct {
    TstNode* root; // Nó raiz da árvore
    unsigned int maxSize; // tamanho da maior palavra presente na árvore
} TreeTrie;

// Cria uma árvore Trie vazia
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
TreeTrie* createTree();

// Cria um nó de árvore Trie vazio
// Pré-condição: Nenhuma
// Pós-condição: Nenhuma
TstNode* createNode();

// Insere uma nova palavra na árvore fornecida
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Palavra inserida na árvore criando os nós necessários
void insert(TreeTrie* tree, char* word);

// Remove uma palavra da árvore Trie fornecida
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Caso a palavra seja encontrada, 1 é retornada e os nós desncessários são removidos,
// caso contrario, 0 é retornado
int removeOne(TreeTrie* tree, char* word);

// Imprime todas as palavras da árvore em ordem alfabetica
// Pré-condição: Ponteiro para árvore Trie valida
// Pós-condição: Nenhuma
void printAsc(TreeTrie* tree);

// Imprime no máximo 10 palavras da árvore que contenham a palavra fornecida como prefixo
// Pré-condição: Ponteiro para árvore Trie válida
// Pós-condição: Nenhuma
void printContainOcorrences(TreeTrie* tree, char* word);

// Encontra nó contendo o final da palavra fornecida
// Pré-condição: Ponteiro para árvore Trie válida
// Pós-condição: Retorna um ponteiro para o nó final da palavra ou NULL caso a palavra não seja encotnrada
TstNode* search(TstNode* node, char* word);

#endif