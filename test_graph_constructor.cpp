#include"vertex.hpp"
#include "graph.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include<unordered_set>
#include<unordered_map>

int main(int argc, char const *argv[])
{
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <data_file> <dimension> <eps>" << std::endl;
        std::cout << "choose dimension = 0 if each row is of the form 'v1' 'v2' 'distance'" << std::endl;
        return 1;
    }

    int dim=std::atoi(argv[2]);
    double eps=std::atof(argv[3]);
    std::cout<<"test"<<std::endl;
    graph g_w_dist(argv[1],eps,dim);

    std::cout << "number of vertices with at least one neighbour:" << g_w_dist.EdgeList.size() << std::endl;
    std::cout << "total number of vertices :" << g_w_dist.VertexList.size() << std::endl;

    std::cout << "first vertices and their neighbours (if there is at least one) :" << std::endl;
    for(auto elem : g_w_dist.EdgeList) {
        if(elem.first->id > 6) continue;
        std::cout << elem.first->id << ": ";
        for(auto v : elem.second) {
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}