#include "graph.hpp"

graph::graph(){
    
}

graph::~graph() { }

void graph::AddVertex(vertex& p){
    VertexList.push_back(p);
}

void graph::AddEdge(vertex& p,vertex& q){
    EdgeList[&p].insert(&q);
}
void graph::RemoveEdge(vertex& p,vertex& q){
    EdgeList[&p].erase(&q);
}
bool graph::HasEdge(vertex& p, vertex& q){
    if(EdgeList[&p].find(&q)==EdgeList[&p].end()){
        return false;
    }
    else
    {
        return true;
    }
    
}