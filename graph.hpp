#pragma once

#include "vertex.hpp"
#include <vector>
#include<unordered_set>
#include<unordered_map>

class graph
{

public:
    graph();
    ~graph();
    graph(const char* file);
    std::unordered_map<vertex*,std::unordered_set<vertex*> > EdgeList;
    std::unordered_map<int,vertex> VertexList;
    void AddVertex(vertex& p);
    bool HasVertex(int id);
    //void RemoveVertex(vertex* p);
    void AddEdge(vertex& p,vertex& q);
    void RemoveEdge(vertex& p, vertex& q);
    bool HasEdge(vertex& p, vertex& q);
    
};
