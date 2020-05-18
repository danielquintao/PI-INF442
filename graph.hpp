#pragma once

#include "vertex.hpp"
#include "point.hpp"
#include <vector>
#include<unordered_set>
#include<unordered_map>

class graph
{

public:
    graph();
    ~graph();
    graph(const char* file, int offset = 0); // constructor for graphs
    graph(const char* file,double eps, int dim); // constructor for N-dim datasets or weighted graphs (dim = 0) 
    std::unordered_map<vertex*,std::unordered_set<vertex*> > EdgeList;
    std::unordered_map<int,vertex> VertexList;
    //std::unordered_map<int,point> PointList;
    void AddVertex(vertex& p);
    bool HasVertex(int id);
    //void RemoveVertex(vertex* p);
    void AddEdge(vertex& p,vertex& q);
    void AddEdge(vertex& p,vertex& q,double dist);
    void RemoveEdge(vertex& p, vertex& q);
    bool HasEdge(vertex& p, vertex& q);
    
};
