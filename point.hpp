#pragma once
#include "vertex.hpp"

class point:public vertex{
public:
    point();
    ~point();
    static int d;
    static int get_dim();
    double* coords;
    double dist(point& p);
};