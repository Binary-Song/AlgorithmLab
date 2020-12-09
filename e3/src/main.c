#include "bintree.h"
#include <stdio.h>
void visit(BinTreeNode* node)
{
    printf("%d ", node->data);
}
int main()
{
    BinTreeNode* t = get_bintree();
    printf("\nforward traverse\n"); 
    fwd_trav(t, visit);
    printf("\nlevel traverse\n");
    lvl_trav(t, visit);

    SBinTree  st;
    st.base = malloc(sizeof(SBinTreeNode) * 200);
    st.size = 0;
    cvt_static(t, &st);
    print_static(&st);
}
// 1 2 5 * * * 3 4 * * * * *
