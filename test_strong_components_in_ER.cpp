#include"vertex.hpp"
#include"graph.hpp"
#include"ER-generator.hpp"
#include"strong-components-detector.hpp"

#include<iostream>
#include<unordered_map>
#include<unordered_set>

int main() {

    int n = 6;
    double prob = 0.3;

    ERGenerator g(n, prob);

    std::cout << "ER digraph generated :\n";
    for(auto elem : g.EdgeList) {
        std::cout << elem.first->id << ": ";
        for(auto v : elem.second) {
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
    }

    StrongComponentDetector detector(5, &g);   
    detector.ComputeStrongConnectedComponents();
    std::cout << "Strongly Connected Components :\n";
    for(int i = 0; i < 6; i++)
    {
        std::cout << "vertex " << i << ": component " << detector.component[i] << std::endl;
    }

    return 0;
}