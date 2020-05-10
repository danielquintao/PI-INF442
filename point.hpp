#pragma once // ensures that this header file is only included once

#include <string>

class point  // this is just a declaration of the class 
             // implementation is in a separate file: point.cpp
{
    static int d; //dimension

public:
    double *coords;
    //int label;

    point();
    ~point();

    void print();
    
};
