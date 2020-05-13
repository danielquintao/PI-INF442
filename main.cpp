#include "graph.hpp"
#include <chrono>
#include <random>

void ER(graph& g,double prob){
    double s=0;
    g.EdgeList.clear();
    for(std::unordered_map<int,vertex>::iterator p=g.VertexList.begin();p!=g.VertexList.end();p++){
        for(std::unordered_map<int,vertex>::iterator q=g.VertexList.begin();q!=p&&q!=g.VertexList.end();q++){
            s=rand()/(double)RAND_MAX;
            if(s<=prob){
                //std::cout<<1<<std::endl;
                g.AddEdge((*p).second,(*q).second);
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
