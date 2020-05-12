#include "graph.hpp"
#include <chrono>
#include <random>

void ER(graph& g,double prob){
    double s=0;
    g.EdgeList.clear();
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




int main(int argc, char const *argv[])
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    
    graph g;

    return 0;
}
