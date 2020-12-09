#include "bintree.h"
#include <stdio.h>
void visit(BinTreeNode* node)
{
    printf("%d ", node->data);
}

int main()
{
    // 1 4 2 * * 7 * * 3 * 5 * * 
    printf("input a tree in preorder:");
    BinTreeNode* t = get_bintree_preorder(); // 先序输入二叉树
    printf("\ntraverse in level-order:\n");
    lvl_trav(t, visit); // 层序遍历（输出）二叉树
 
    SBinTree st = convert_to_static_tree(t); // 转为静态二叉树
    print_static_tree(&st);// 输出
    free_static_tree(st);// 回收资源
    free_bintree(t);
}
