#include "TreeTrie.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

void insert(TreeTrie *tree, char *word) {
    tree->root = aux_insert(tree->root, word);
    if (strlen(word) > tree->maxSize) {
        tree->maxSize = strlen(word);
    }
}

TstNode *createNode() {
    TstNode* node = malloc(sizeof(TstNode));
    node->minor = NULL;
    node->greater = NULL;
    node->equal = NULL;
    node->chr = '\0';
    node->isFinal = 0;
    return node;
}

TreeTrie *createTree() {
    TreeTrie* tree = malloc(sizeof(TreeTrie));
    tree->root = NULL;
    tree->maxSize = 0;
    return tree;
}

void aux_printAsc(TstNode* node, char* prefix, int* limit) {
    if (node == NULL)
        return;

    unsigned int length = strlen(prefix);
    aux_printAsc(node->minor, prefix, limit);

    prefix[length + 1] = '\0';
    prefix[length] = node->chr;

    if (node->isFinal) {
        if (*limit == 0 )
            return;
        if (*limit > 0)
            *limit = (*limit) - 1;
        printf("%s\n", prefix);
    }

    aux_printAsc(node->equal, prefix, limit);

    prefix[length] = '\0';
    aux_printAsc(node->greater, prefix, limit);
}

void printAsc(TreeTrie *tree) {
    char prefix[tree->maxSize];
    prefix[0] = '\0';
    if (tree->root != NULL) {
        int limit = -1;
        aux_printAsc(tree->root, prefix, &limit);
    }
}

TstNode* search(TstNode* node, char* word) {
    if (node == NULL)
        return NULL;

    if (node->chr == *word) {
        if (*(word + 1) == '\0')
            return node;
        else
            return search(node->equal,word+1);
    } else if (*word < node->chr)
        node->minor = search(node->minor, word);
    else
        node->greater = search(node->greater, word);
}

void printContainOcorrences(TreeTrie *tree, char* word) {
    if (*word == '\0')
        return;

    TstNode* findNode = search(tree->root, word);
    if (findNode != NULL) {
        int rest = 10;
        if (findNode->isFinal) {
            printf("%s",word);
            rest--;
        }
        char prefix[tree->maxSize];
        strcpy(prefix, word);
        aux_printAsc(findNode->equal, prefix, &rest);
    }
}

TstNode* aux_remove(TstNode* node, char* str, int* findFlag) {
    if (node == NULL || *str == '\0') {
        *findFlag = 0;
        return node;
    }

    if (*str == node->chr) {
        if (*(str+1) != '\0') {
            node->equal = aux_remove(node->equal, str+1, findFlag);
        } else {
            node->isFinal = 0;
            *findFlag = 1;
        }
    } else if (*str > node->chr) {
        node->greater = aux_remove(node->greater, str, findFlag);
    } else {
        node->minor = aux_remove(node->minor, str, findFlag);
    }

    if (node->minor == NULL && node->greater == NULL && node->equal == NULL && !node->isFinal) {
        free(node);
        node = NULL;
    }

    return node;
}

void removeOne(TreeTrie *tree, char *word) {
    int findFlag = 0;
    tree->root = aux_remove(tree->root, word, &findFlag);
    if (!findFlag) {
        printf("Palavra nao encontrada no dicionario: %s\n", word);
    }
}
