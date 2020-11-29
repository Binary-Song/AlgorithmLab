#include "polyn.h"
#include <stdio.h>
int main()
{
    double expo1[] = { 1,2,3,4 };
    double coef1[] = { 5,3,4,6 };

    double expo2[] = { 1,3,4,6,7 };
    double coef2[] = { 4,-4,1,6,1 };

    Polyn* p1 = init_polyn(4, expo1, coef1, stdin);
    Polyn* p2 = init_polyn(5, expo2, coef2, stdin);

    Polyn* psum = add_sorted_polyn(p1, p2);

    print_polyn(p1, stdout);
    printf("+\n");
    print_polyn(p2, stdout);
    printf("=\n");
    print_polyn(psum, stdout);

    deinit_polyn(p1);
    deinit_polyn(p2);
    deinit_polyn(psum);
    printf("memory leak count = %d\n", memory_leaks);
}