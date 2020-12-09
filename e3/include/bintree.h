#ifndef _BINTREE_H_
#define _BINTREE_H_
#include <stdlib.h>
typedef int data_t;
#define data_fmt "%d"

/// 二叉树节点
typedef struct BinTreeNode
{
    /// 左孩子
    struct BinTreeNode* lchild;
    /// 右孩子
    struct BinTreeNode* rchild;
    /// 数据
    data_t data;
} BinTreeNode;

/// 静态二叉树节点
typedef struct SBinTreeNode
{
    /// 左孩子
    int lchild;
    /// 右孩子
    int rchild;
    /// 数据
    data_t data;
}SBinTreeNode;

/// 静态二叉树
typedef struct SBinTree
{
    /// 节点数组
    SBinTreeNode* base;
    /// 大小
    size_t size;
}SBinTree;

/// 输入先序创建的二叉树
BinTreeNode* get_bintree_preorder();

/// 回收二叉树
void free_bintree(BinTreeNode* tree);

/// 层序遍历
void lvl_trav(BinTreeNode* root, void (*visit)(BinTreeNode* node));

/// 转为静态二叉树
SBinTree convert_to_static_tree(BinTreeNode* root);

/// 回收静态二叉树
void free_static_tree(SBinTree st);

/// 输出静态二叉树
void print_static_tree(SBinTree* tree);
#endif // _BINTREE_H_