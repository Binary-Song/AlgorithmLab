#include <iostream>
#include "matrix.h"
#include "graph_algo.h"
#include "display.h"
#include <time.h>
int main(int argc, char* argv[])
{
    time_t t;
    time(&t);
    srand(t);
    Graph graph;
    Matrix mat(10, 10, Matrix::InitMethod::Random);
    graph.draw_map(mat, 300, 300, 0.1f);
    Matrix mat2(10, 10, Matrix::InitMethod::Random);

    graph.draw_map(mat2, 300, 300, 0.5f);
    getchar();
}