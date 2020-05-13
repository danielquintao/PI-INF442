#include"vertex.hpp"
#include"graph.hpp"
#include"ER-generator.hpp"

#include<iostream>
#include<unordered_map>
#include<unordered_set>

int main() {

    int n = 6;
    double prob = 0.5;

    ERGenerator g(n, prob);

    for(auto elem : g.EdgeList) {
        std::cout << elem.first->id << ": ";
        for(auto v : elem.second) {
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
    }
    

    return 0;
}