#include"point.hpp"
#include<cmath>

point::point() {
    coords = new double[d];
    for(int i = 0; i < d; i++)
    {
        coords[i] = 0; // default
    }
}

point::~point() {
    delete[] coords;
}

int point::d = 2; // default

int point::get_dim() {
    return d;
}

double point::dist(point& p)
{
    double res = 0;
    for(int i = 0; i < d; i++)
    {
        res += (coords[i] - p.coords[i]) * (coords[i] - p.coords[i]);
    }
    return std::sqrt(res);
}
