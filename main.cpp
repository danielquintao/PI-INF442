#include "graph.hpp"
#include <chrono>
#include <random>

void ER(graph& g,double prob){
    double s=0;
    for(std::vector<point> ::iterator p=g.VertexList.begin();p!=g.VertexList.end();p++){
        for(std::vector<point> ::iterator q=g.VertexList.begin();q!=p&&q!=g.VertexList.end();q++){
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		    srand(seed);
            s=rand()/RAND_MAX;
            if(s<=prob){
                g.AddEdge(*p,*q);
            }
        }
    }
}




int main(int argc, char const *argv[])
{
    graph g;

    return 0;
}
