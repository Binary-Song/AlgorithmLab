#ifndef _POLYN_H_
#define _POLYN_H_

#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

/// 多项式节点
typedef struct Polyn
{
    /// 后继节点
    struct Polyn* next;
    /// 数据域
    struct
    {
        /// 指数
        int expo;
        /// 系数
        double coef;
    } term;
} Polyn;

/// 给定数组，从中读取多项式。*返回的内存要用deinit_polyn回收*
/// size - 多项式项数
/// expo - 指数组成的数组
/// coef - 系数组成的数组
Polyn* init_polyn(size_t size, double coef[], int expo[]);

/// 回收多项式链表。
/// p - 多项式的指针
void deinit_polyn(Polyn* p);

/// 将两个升幂排列的多项式相加，不破坏原来的多项式，返回结果多项式。*返回的内存要用deinit_polyn回收*
/// p1 - 多项式1
/// p2 - 多项式2
Polyn* add_polyn(const Polyn* p1, const Polyn* p2);

/// 输出多项式。
/// p - 多项式
void print_polyn(const Polyn* p);
#endif // _POLYN_H_