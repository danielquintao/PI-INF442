#include "point.hpp" // include the header file

#include <iostream> // for cout, endl for printing


point::point()
{
    coords = new double[d];

    for (int m = 0; m < d; m++)
        coords[m] = 0.0;

    //label = 0;
}

point::~point()
{
    delete[] coords;
}

void point::print()
{
    for (int j = 0; j < d; j++)
        std::cout <<coords[j] << ' ';

    //std::cout << etiquette;
}


int point::d = 0; 


