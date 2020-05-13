#include "graph.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }

	graph g(argv[1]);

    return 0;
}