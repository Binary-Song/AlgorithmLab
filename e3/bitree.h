typedef int data_t;

typedef struct bintree
{
    struct bintree* lchild;
    struct bintree* rchild;
    data_t data;
} bintree;

bintree* init_bintree();
void deinit_bintree(bintree* tree);