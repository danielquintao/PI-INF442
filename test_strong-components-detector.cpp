#include"vertex.hpp"
#include"graph.hpp"
#include"strong-components-detector.hpp"
#include<iostream>

int main()
{
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

    g.AddEdge(v1, v2);
    g.AddEdge(v2, v3);
    g.AddEdge(v2, v8);
    g.AddEdge(v3, v4);
    g.AddEdge(v3, v7);
    g.AddEdge(v4, v5);
    g.AddEdge(v5, v3);
    g.AddEdge(v5, v6);
    g.AddEdge(v7, v4);
    g.AddEdge(v7, v6);
    g.AddEdge(v8, v1);
    g.AddEdge(v8, v7);

    StrongComponentDetector detector(8, &g);

    detector.ComputeStrongConnectedComponents();

    for(int i = 0; i < 8; i++)
    {
        std::cout << "vertex " << i << ": component " << detector.component[i] << std::endl;
    }
    std::cout << "We should have three components, with one, three and four vertices\n";

    return 0;
}