#ifndef TRIETREE_TREETRIE_H
#define TRIETREE_TREETRIE_H

typedef struct TstNode {
    char chr;
    int isFinal;
    struct TstNode *minor;
    struct TstNode *equal;
    struct TstNode *greater;
} TstNode;

typedef struct {
    TstNode* root;
    unsigned int maxSize;
} TreeTrie;

TreeTrie* createTree();

TstNode* createNode();

void insert(TreeTrie* tree, char* word);

void removeOne(TreeTrie* tree, char* word);

void printAsc(TreeTrie* tree);

void printContainOcorrences(TreeTrie* tree, char* word);

#endif