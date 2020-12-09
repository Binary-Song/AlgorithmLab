#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NO_DATA 1
#define HAS_DATA 0

/// gets data from stdin to fill into node->data
/// returns 1 if no data, otherwise 0 
static int get_data(data_t* data)
{
    data_t in_data;
    char in_char;
    int scan_ret = scanf(data_fmt, &in_data);
    if (scan_ret == 1) { // valid data
        *data = in_data;
        return HAS_DATA;
    }
    if (scanf("%c", &in_char) == 1 && in_char == '*') {
        return NO_DATA;
    }
    printf("unexpected data\n");
    abort();
}

void fwd_get_bintree_rcrs(BinTreeNode** root)
{
    data_t data;
    if (get_data(&data) == NO_DATA) {
        *root = NULL;
    }
    else {
        (*root) = malloc(sizeof(BinTreeNode));
        (*root)->data = data;
        fwd_get_bintree_rcrs(&((*root)->lchild));
        fwd_get_bintree_rcrs(&((*root)->rchild));
    }
}

BinTreeNode* get_bintree()
{
    BinTreeNode* tree = malloc(sizeof(BinTreeNode));
    fwd_get_bintree_rcrs(&tree);
    return tree;
}

// 1 2 * 3 * 
void free_bintree(BinTreeNode* tree)
{
    if (!tree) return;
    BinTreeNode* l = tree->lchild, * r = tree->rchild;

    free(tree);
    free_bintree(l);
    free_bintree(r);
}

void fwd_trav(BinTreeNode* root, void (*visit)(BinTreeNode* node))
{
    if (!root) return;
    visit(root);
    fwd_trav(root->lchild, visit);
    fwd_trav(root->rchild, visit);
}

typedef struct Queue
{
    BinTreeNode** base;
    size_t front;
    size_t rear;
    size_t size;
}Queue;

void enqueue(Queue* queue, BinTreeNode* node)
{
    if ((queue->rear + 1) % queue->size == queue->front % queue->size) {
        fprintf(stderr, "queue overflow\n");
        abort();
    }
    queue->base[queue->rear] = node;
    queue->rear++;
    queue->rear %= queue->size;
}

BinTreeNode* dequeue(Queue* queue)
{
    if (queue->front % queue->size == queue->rear % queue->size) {
        fprintf(stderr, "queue overflow\n");
        abort();
    }
    BinTreeNode* node = queue->base[queue->front];
    queue->front++;
    queue->front %= queue->size;
    return node;
}

void lvl_trav(BinTreeNode* root, void (*visit)(BinTreeNode* node))
{
    if (!root) return;

    Queue q;
    q.base = malloc(sizeof(BinTreeNode) * 300);
    q.front = 0;
    q.rear = 0;
    q.size = 300;

    enqueue(&q, root);
    while (q.front != q.rear) {
        BinTreeNode* front_node = dequeue(&q);
        if (front_node) {
            visit(front_node);
            enqueue(&q, front_node->lchild);
            enqueue(&q, front_node->rchild);
        }
    }

    free(q.base);
}

size_t cvt_static(BinTreeNode* root, SBinTree* stree)
{
    stree->base[stree->size].data = root->data;
    size_t index = stree->size;
    stree->size += 1;
    if (root->lchild) {
        stree->base[index].lchild = cvt_static(root->lchild, stree);
    }
    else {
        stree->base[index].lchild = -1;
    }

    if (root->rchild) {
        stree->base[index].rchild = cvt_static(root->rchild, stree);
    }
    else {
        stree->base[index].rchild = -1;
    }
    return   stree->size - 1;
}

void print_static(SBinTree* tree)
{
    printf("\nstatic tree: ");
    for (int i = 0; i < tree->size; i++) {
        printf("\nindex = %d   data = %d   lchild = %d   rchild = %d",i, tree->base[i].data, tree->base[i].lchild, tree->base[i].rchild);
    }
}