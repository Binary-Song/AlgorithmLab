#include "polyn.h"
#include <stdio.h>
/// 给定数组，从中读取多项式。返回的Polyn*要用deinit_polyn回收
/// size - 多项式项数，即数组的长度
/// expo - 指数组成的数组
/// coef - 系数组成的数组
Polyn* init_polyn(size_t size, double coef[], int expo[])
{
    Polyn* head = malloc(sizeof(Polyn)); // 头节点
    Polyn* p = head;
    for (size_t i = 0; i < size; i++) { // 遍历数组添加节点
        p->next = malloc(sizeof(Polyn));
        p = p->next;
        p->term.coef = coef[i];
        p->term.expo = expo[i];
    }
    p->next = NULL;
    return head;
}

/// 回收多项式链表。
/// p - 多项式的指针
void deinit_polyn(Polyn* p)
{
    while (p->next) { // 不断删除第一个
        Polyn* saved = p->next;
        p->next = p->next->next;
        free(saved);
    }
    free(p); // 回收头节点
}

/// 将两个升幂排列的多项式相加，不破坏原来的多项式，返回结果多项式。返回的Polyn*要用deinit_polyn回收。
/// p1 - 多项式1
/// p2 - 多项式2
Polyn* add_polyn(const Polyn* p1_head, const Polyn* p2_head)
{
    Polyn* r_head = malloc(sizeof(Polyn)); // 结果多项式的头
    Polyn* r = r_head; // 指向结果的尾节点
    Polyn* p1 = p1_head->next, * p2 = p2_head->next; // 指向p1p2的尾节点

    while (p1 || p2) { // p1 p2不全为空
        int take_who = 0; //表示选择p1(值为1)还是p2(值为2)还是都要(值为3)的flag
        if (!p1) {// p1空且p2不空
            take_who = 2; // 选择p2
        }
        else if (!p2) {// p1不空且p2空
            take_who = 1;  // 选择p1
        }
        else { // p1 p2 全不为空
            if (p1->term.expo > p2->term.expo) { // p2 指数小
                take_who = 2; // 选p2
            }
            else if (p1->term.expo < p2->term.expo) {  // p1 指数小
                take_who = 1;// 选p1
            }
            else take_who = 3; // 指数一样大，都要
        }

        if (take_who == 1) { // 如果选p1
            r->next = malloc(sizeof(Polyn));
            r = r->next;
            r->term = p1->term;
            p1 = p1->next;
        }
        else if (take_who == 2) {// 如果选p2
            r->next = malloc(sizeof(Polyn));
            r = r->next;
            r->term = p2->term;
            p2 = p2->next;
        }
        else if (take_who == 3) {// 如果都要
            double sum = p1->term.coef + p2->term.coef;
            if (sum) {
                r->next = malloc(sizeof(Polyn));
                r = r->next;
                r->term.coef = p1->term.coef + p2->term.coef;
                r->term.expo = p1->term.expo;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        else abort();
    }
    r->next = NULL; // 尾节点置空
    return r_head;
}

/// 输出多项式。
/// p - 多项式
void print_polyn(const Polyn* p_h)
{
    int first = 1;
    Polyn* p = p_h->next;
    while (p) { 
        if (first) first = 0;
        else printf("  +  "); // 不是第一次，就需要输出加号
        switch (p->term.expo) {
        case 0:
            printf("%4.2lf        ", p->term.coef);// 指数为0
            break;
        case 1:
            printf("%4.2lf x      ", p->term.coef);// 指数为1
            break;
        default: // 指数非0非1
            printf("%4.2lf x ^ %-3d", p->term.coef, p->term.expo);
        } 
        p = p->next;
    }
    putchar('\n');
}