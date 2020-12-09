#ifndef _BINTREE_H_
#define _BINTREE_H_
#include <stdlib.h>
typedef int data_t;
#define data_fmt "%d"

typedef struct BinTreeNode
{
    struct BinTreeNode* lchild;
    struct BinTreeNode* rchild;
    data_t data;
} BinTreeNode;

typedef struct SBinTreeNode
{
    size_t lchild;
    size_t rchild;
    data_t data;
}SBinTreeNode;

typedef struct SBinTree
{
    SBinTreeNode* base;
    size_t size;
}SBinTree;

BinTreeNode* get_bintree();

void free_bintree(BinTreeNode* tree);

void fwd_trav(BinTreeNode* root, void (*visit)(BinTreeNode* node));

void lvl_trav(BinTreeNode* root, void (*visit)(BinTreeNode* node));

size_t cvt_static(BinTreeNode* root, SBinTree* tree);

void print_static(SBinTree* tree);
#endif // _BINTREE_H_