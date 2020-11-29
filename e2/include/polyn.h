#ifndef _POLYN_H_
#define _POLYN_H_

#include <stdlib.h>
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
        double expo;
        /// 系数
        double coef;
    } term;
} Polyn;

/// 给定文件流，从中读取多项式。格式：项数 系数1 指数1 系数2 指数2 ......
/// 例如：3 1 2 2 1 1 0 表示 x^2 + 2x + 1
/// 返回多项式链表的指针。内存要用deinit_polyn回收。
Polyn* init_polyn(size_t size, double expo[], double coef[] );

/// 回收多项式链表。
void deinit_polyn(Polyn* p);

/// 将两个升幂排列的多项式相加，不破坏原来的多项式，返回结果多项式。
/// 内存要用deinit_polyn回收。
Polyn* add_polyn(const Polyn* p1_head, const Polyn* p2_head);

/// 输出多项式到指定的文件流。
void print_polyn(const Polyn* p, FILE* file);
#endif // _POLYN_H_