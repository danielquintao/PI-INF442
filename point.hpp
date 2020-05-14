#pragma once

class point{
public:
    point();
    ~point();
    static int d;
    static int get_dim();
    double* coords;
    double dist(point& p);
};