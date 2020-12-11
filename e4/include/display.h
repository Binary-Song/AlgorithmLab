#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "matrix.h"

class Graph
{
private:
    int w, h;
    int center_x, center_y;
    void get_node_position(double i, double n, double& x, double& y);

public:
    Graph(int w = 1200,int h= 800);
    ~Graph();
    void draw_map(const Matrix& mat, int cx, int cy, float hue);
};

#endif // _DISPLAY_H_