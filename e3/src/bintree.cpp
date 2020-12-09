#include "bintree.h"
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NO_DATA 1
#define HAS_DATA 0

/// 从stdin获取数据，填入指针。返回是否有数据。
static int get_data(data_t* data)
{
    data_t in_data;
    char in_char;
    int scan_ret = scanf(data_fmt, &in_data);
    if (scan_ret == 1) { // 有效数据
        *data = in_data;
        return HAS_DATA;
    }
    if (scanf("%c", &in_char) == 1 && in_char == '*') {
        return NO_DATA;
    }
    printf("unexpected data\n");
    abort();
}

/// 递归先序输入二叉树
void fwd_get_bintree_rcrs(BinTreeNode** root)
{
    data_t data;
    if (get_data(&data) == NO_DATA) {
        *root = NULL;
    }
    else {
        (*root) = (BinTreeNode*)malloc(sizeof(BinTreeNode));
        (*root)->data = data;
        fwd_get_bintree_rcrs(&((*root)->lchild));
        fwd_get_bintree_rcrs(&((*root)->rchild));
    }
}

/// 先序输入二叉树
BinTreeNode* get_bintree_preorder()
{
    BinTreeNode* tree = (BinTreeNode*)malloc(sizeof(BinTreeNode));
    fwd_get_bintree_rcrs(&tree);
    return tree;
}

/// 回收二叉树的内存
void free_bintree(BinTreeNode* tree)
{
    if (!tree) return;
    BinTreeNode* l = tree->lchild, * r = tree->rchild;
    free(tree);
    free_bintree(l);
    free_bintree(r);
}

/// 层序遍历
void lvl_trav(BinTreeNode* root, void (*visit)(BinTreeNode*))
{
    using std::queue;
    if (!root) return;

    queue<BinTreeNode*> q;
    q.push(root);

    while (!q.empty()) { // 队列为空，遍历结束
        BinTreeNode* front_node = q.front();
        q.pop();
        if (front_node) {
            visit(front_node);
            q.push(front_node->lchild);
            q.push(front_node->rchild);
        }
    }
}
 
/// 递归转为静态树，返回节点在静态树中的位置
int convert_to_static_tree_impl(BinTreeNode* root, SBinTree* st)
{
    if (!root) return -1;
    SBinTreeNode* end = st->base + st->size;
    st->size += 1;
    end->data = root->data;
    end->lchild = convert_to_static_tree_impl(root->lchild, st);
    end->rchild = convert_to_static_tree_impl(root->rchild, st);
    return end - st->base;
}

/// 非递归外壳函数
SBinTree convert_to_static_tree(BinTreeNode* root)
{
    SBinTree st;
    st.base = (SBinTreeNode*)malloc(sizeof(SBinTreeNode) * 100);
    st.size = 0;
    convert_to_static_tree_impl(root, &st);
    return st;
}

/// 输出静态树
void print_static_tree(SBinTree* tree)
{
    printf("\nstatic tree: ");
    for (int i = 0; i < tree->size; i++) {
        printf("\nindex = %2d  lchild = %2d  rchild = %2d  data = %2d", i, tree->base[i].lchild, tree->base[i].rchild, tree->base[i].data);
    }
}

/// 回收静态树
void free_static_tree(SBinTree st)
{
    free(st.base);
}