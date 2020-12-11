#define _USE_MATH_DEFINES
#include "display.h"
#include <math.h>
#include "easyx.h"
#include <string>
#include "graphics.h"

#define NODE_MAP_RADIUS 150
#define NODE_RADIUS 15
#define TEXT_X_OFFSET (-3)
#define TEXT_Y_OFFSET (-7)
#define ARROW_HEAD_HEIGHT 15
#define ARROW_HEAD_WIDTH 5

Graph::Graph(int w, int h) :w(w), h(h)
{
    initgraph(w, h);
}

Graph::~Graph()
{
    closegraph();
}

/// 单位方向向量
static void ndir(double x1, double y1, double x2, double y2, double& xn, double& yn)
{
    double mod = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    xn = (x2 - x1) / mod;
    yn = (y2 - y1) / mod;
}

static void arrow(double x1, double y1, double x2, double y2)
{
    line((int)x1, (int)y1, (int)x2, (int)y2);
    double xt, yt;
    ndir(x1, y1, x2, y2, xt, yt);
    double xn = yt, yn = -xt;
    xt *= ARROW_HEAD_HEIGHT;
    yt *= ARROW_HEAD_HEIGHT;
    xn *= ARROW_HEAD_WIDTH;
    yn *= ARROW_HEAD_WIDTH;
    POINT pts[] = { { (int)x2, (int)y2}, {int(x2 - xt + xn), int(y2 - yt + yn)}, {int(x2 - xt - xn), int(y2 - yt - yn)} };
    solidpolygon(pts, 3);
}

void Graph::get_node_position(double i, double n, double& x, double& y)
{
    double theta = -i / n * 2 * M_PI;
    x = double(center_x + NODE_MAP_RADIUS * cos(theta));
    y = double(center_y + NODE_MAP_RADIUS * sin(theta));
}

void Graph::draw_map(const Matrix& mat, int cx, int cy, float color)
{
    center_x = cx;
    center_y = cy;
    if (mat.col() != mat.row()) throw "need a square matrix";
    int n = mat.col();
    for (int i = 0; i < n; i++) {
        double x = 0, y = 0;
        get_node_position(i, n, x, y);
        circle((int)x, (int)y, NODE_RADIUS);
        std::string text = std::to_string(i);
        outtextxy(int(x + TEXT_X_OFFSET), int(y + TEXT_Y_OFFSET), text.c_str());
        double xend = 0, yend = 0;
        for (int j = 0; j < n; j++) {
            if (mat(i, j)) {
                get_node_position(j, n, xend, yend);
                double xn = 0, yn = 0;
                ndir(x, y, xend, yend, xn, yn);
                xn *= NODE_RADIUS;
                yn *= NODE_RADIUS;

                COLORREF oclr = getlinecolor();
                COLORREF nclr = HSVtoRGB(color * 360, 1, 1);
                setlinecolor(nclr);
                setfillcolor(nclr);
                arrow(x + xn, y + yn, xend - xn, yend - yn);
                setlinecolor(oclr);
                setfillcolor(oclr);
            }
        }
    }
}