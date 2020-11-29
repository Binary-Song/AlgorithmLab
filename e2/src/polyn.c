#include "polyn.h"
#include <stdio.h>

Polyn* init_polyn(size_t size, double expo[], double coef[])
{
    Polyn* head = malloc(sizeof(Polyn));
    Polyn* p = head;
    for (size_t i = 0; i < size; i++) {
        p->next = malloc(sizeof(Polyn));
        p = p->next;
        p->term.coef = coef[i];
        p->term.expo = expo[i];
    }
    p->next = NULL;
    return head;
}

void deinit_polyn(Polyn* p)
{
    while (p->next) {
        Polyn* saved = p->next;
        p->next = p->next->next;
        free(saved);
    }
    free(p);
}

Polyn* add_polyn(const Polyn* p1_head, const Polyn* p2_head)
{
    Polyn* r_head = malloc(sizeof(Polyn));
    Polyn* r = r_head;
    Polyn* p1 = p1_head->next, * p2 = p2_head->next;

    while (p1 || p2) {
        int take_who = 0; // 1 p1, 2 p2, 3 add p1 p2
        if (!p1) {// !p1 && p2
            take_who = 2;
        }
        else if (!p2) {// p1 && !p2
            take_who = 1;
        }
        else { // p1 && p2
            if (p1->term.expo > p2->term.expo) { // p2 is smaller
                take_who = 1;
            }
            else if (p1->term.expo < p2->term.expo) { // p1 is smaller
                take_who = 2;
            }
            else take_who = 3;
        }

        if (take_who == 1) {
            r->next = malloc(sizeof(Polyn));
            r = r->next;
            r->term = p1->term;
            p1 = p1->next;
        }
        else if (take_who == 2) {
            r->next = malloc(sizeof(Polyn));
            r = r->next;
            r->term = p2->term;
            p2 = p2->next;
        }
        else if (take_who == 3) {
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
    r->next = NULL;
    return r_head;
}

void print_polyn(const Polyn* p_h)
{
    int first = 1;
    Polyn* p = p_h->next;
    while (p) {
        if (first) {
            printf("%3.0lfx ^ %-3.0lf", p->term.coef, p->term.expo);
            first = 0;
        }
        else {
            printf("  +  %3.0lfx ^ %-3.0lf", p->term.coef, p->term.expo);
        }
        p = p->next;
    }
    putchar('\n');
}