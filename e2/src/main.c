#include <stdio.h>
#include "polyn.h"

/// 从stdin取得多项式的参数，格式：项数N 系数1 指数1 系数2 指数2 ...... 系数N 指数N 
void get_polyn_parameters(unsigned* n, double coef[], int expn[]);

/// 主函数
int main()
{
    // 缓存
    int expn[10] = { 0 };
    double coef[10] = { 0 };
    unsigned n;

    // 输入多项式1
    printf("Enter polynomial 1. Format: N coef1 expn1 coef2 expn2 ... coefN expnN\n");
    get_polyn_parameters(&n, coef, expn); // 从stdin取得参数，保存到缓存
    Polyn* p1 = init_polyn(n, coef, expn); // 用缓存中的参数创建多项式链表p1

    // 输入多项式2
    printf("Enter polynomial 2. Format: N coef1 expn1 coef2 expn2 ... coefN expnN\n");
    get_polyn_parameters(&n, coef, expn); // 从stdin取得参数，保存到缓存
    Polyn* p2 = init_polyn(n, coef, expn); // 用缓存中的参数多项式链表p2

    printf("Input:\nP1 = ");
    print_polyn(p1); // 输出相加前的p1
    printf("P2 = ");
    print_polyn(p2); // 输出相加前的p2

    printf("Computing...\n");
    Polyn* psum = add_polyn(p1, p2); // 执行p1+p2

    printf("Output:\nP1 + P2 =\n");
    print_polyn(p1);// 输出相加后的p1，证明其未被破坏
    printf("+\n");
    print_polyn(p2);// 输出相加后的p2，证明其未被破坏
    printf("=\n");
    print_polyn(psum);// 输出多项式和psum

    deinit_polyn(p1); // 回收内存
    deinit_polyn(p2);
    deinit_polyn(psum);
}

void get_polyn_parameters(unsigned* n, double coef[], int expn[])
{
    scanf("%ud", n);
    *n = *n % 10;
    for (size_t i = 0; i < *n; i++) {
        scanf("%lf %d", coef + i, expn + i);
    }
}
/*
3 1 0 2 1 3 2
4 1 -1 1 1 -3 2 5 4

*/