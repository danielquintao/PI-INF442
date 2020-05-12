#include"vertex.hpp"
#include"graph.hpp"
#include<iostream>
#include <chrono>
#include <random>

void ER(graph& g,double prob){
    double s=0;
    g.EdgeList.clear();
    // for(std::vector<vertex> ::iterator p=g.VertexList.begin();p!=g.VertexList.end();p++){
    //     for(std::vector<vertex> ::iterator q=g.VertexList.begin();q!=p&&q!=g.VertexList.end();q++){
    //         s=rand()/(double)RAND_MAX;
    //         if(s<=prob){
    //             //std::cout<<1<<std::endl;
    //             g.AddEdge((*p),(*q));
    //         }
    //     }
    // }
    for(int i=0;i<g.VertexList.size();i++){
        for(int j=0;j<g.VertexList.size();j++){
            if(i!=j){
                s=rand()/(double)RAND_MAX;
                if(s<=prob){
                    //std::cout<<1<<std::endl;
                    g.AddEdge(g.VertexList[i],g.VertexList[j]);
                }
            }
        }
    }
}
int main()
{   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    vertex v1, v2, v3, v4, v5, v6, v7, v8;
    v1.id = 0;
    v2.id = 1;
    v3.id = 2;
    v4.id = 3;
    v5.id = 4;
    v6.id = 5;
    v7.id = 6;
    v8.id = 7;

    graph g;

    g.AddVertex(v1);
    g.AddVertex(v2);
    g.AddVertex(v3);
    g.AddVertex(v4);
    g.AddVertex(v5);
    g.AddVertex(v6);
    g.AddVertex(v7);
    g.AddVertex(v8);

    int count =0;
    int n=100;
    double prob=0.7;
    for(int i=0;i<n;i++){
        ER(g,prob);
        if(g.HasEdge(g.VertexList[0],g.VertexList[6])){
            //std::cout<<1<<std::endl;
            count++;
        }
    }
    std::cout<<prob-count/(double)n<<std::endl;
    
    return 0;
}