#include"strong-components-detector.hpp"
#include"graph.hpp"
#include"vertex.hpp"
#include"point.hpp"

#include<iostream>
#include<fstream>
#include<chrono>
#include<algorithm>

int main(int argc, char const *argv[]) {

    if (argc < /*3*/2) {
        std::cout << "Usage: " << argv[0] << " <data_file>" /*<< " <start_in_zero: 1 or 0>"*/ << std::endl;
        return 1;
    }

    graph g(argv[1]/*, std::atoi(argv[2])*/);

    std::cout << "number of vertices with at least one neighbour:" << g.EdgeList.size() << std::endl;
    std::cout << "total number of vertices :" << g.VertexList.size() << std::endl;

    int max_id;
    /*if(std::atoi(argv[2]))*/ max_id = g.VertexList.size()-1;
    /*else max_id = g.VertexList.size();*/
    StrongComponentDetector detector(max_id, &g);
    auto time1 = std::chrono::high_resolution_clock::now();
    detector.ComputeStrongConnectedComponents();
    auto time2 = std::chrono::high_resolution_clock::now();

    // vertices in largest component :
    //int n_comp = (*std::max_element(detector.component, detector.component + sizeof(detector.component)/sizeof(int)));
    int n_comp = (*std::max_element(detector.component, detector.component + max_id + 1));
    std::cout << "debug " << n_comp << std::endl;
    int* n_vertices = new int[n_comp];
    for(int i = 0; i < n_comp; i++)
    {
        n_vertices[i] = 0;
    }
    for(auto v : g.VertexList)
    {
        int j = detector.component[v.second.id];
        //if(j < 1 || j > n_comp) std::cout << "!!!! " << j << std::endl;
        if(j == -1) continue;
        n_vertices[j-1]++; // "-1" because component numbering start in 1
    }
    std::cout << "debug\n";
    int elem_in_max_SCC = (*std::max_element(n_vertices, n_vertices + n_comp));

    std::cout << "total of " << n_comp << " components" << std::endl;
    std::cout << "numb of vertices in SCCP " << elem_in_max_SCC << std::endl;
    std::cout << "time to tarjan algo (without kd-tree construction): " << std::chrono::duration_cast<std::chrono::milliseconds>(time2-time1).count() << " ms" << std::endl;

    return 0;
}