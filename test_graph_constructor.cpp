#include"vertex.hpp"
#include "graph.hpp"
#include <chrono>
#include <random>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include<unordered_set>
#include<unordered_map>

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <data_file>" << std::endl;
        return 1;
    }

	graph g(argv[1]);

    for(auto elem : g.EdgeList) {
        if(elem.first->id > 6) continue;
        std::cout << elem.first->id << ": ";
        for(auto v : elem.second) {
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
    }
    

    /* same results */
    /*for(std::unordered_map<vertex*,std::unordered_set<vertex*> >::iterator it = g.EdgeList.begin(); it != g.EdgeList.end(); it++)
    {
        if(it->first->id > 6) continue;
        std::cout << it->first->id << ": ";
        for(std::unordered_set<vertex*>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            vertex* v =  (*it2);
            std::cout << v->id << " ";
        }
        std::cout << std::endl;
    }
    */

    return 0;
}