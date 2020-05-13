#include"ER-generator.hpp"

#include<iostream>
#include <chrono>
#include <random>

ERGenerator::ERGenerator(int n, double prob) : graph() {
    // creating n vertices
    for(int i = 0; i < n; i++)
    {
        vertex v;
        v.id = i;
        AddVertex(v);
    }
    // adding Edges
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    double s = 0;
    for(std::unordered_map<int,vertex>::iterator p=VertexList.begin();p!=VertexList.end();p++){
        for(std::unordered_map<int,vertex>::iterator q=VertexList.begin();q!=p&&q!=VertexList.end();q++){
            s=rand()/(double)RAND_MAX;
            if(s<=prob){
                //std::cout<<1<<std::endl;
                AddEdge((*p).second,(*q).second);
            }
        }
    }
};

ERGenerator::~ERGenerator() {};