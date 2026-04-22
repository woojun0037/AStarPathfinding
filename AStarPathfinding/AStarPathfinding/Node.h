#pragma once
#include "Common.h"

struct Node
{
    int x;
    int y;
    int g;
    int h;
    int f;
    int parentX;
    int parentY;

    Node(): x(0), y(0), g(0), h(0), f(0), parentX(-1), parentY(-1)
    {
    }

    Node(int x, int y, int g, int h, int parentX, int parentY): 
    x(x),  y(y),  g(g),  h(h), f(g + h), parentX(parentX), parentY(parentY)
    {
    }
};





