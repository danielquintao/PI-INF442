#pragma once

#include"graph.hpp"
#include"vertex.hpp"

#include<stack>
#include<iostream>
#include<algorithm>

class StrongComponentDetector {

public:
    StrongComponentDetector(int max_id, graph* graph_);
    ~StrongComponentDetector();
    graph* graph_;
    int max_id; // maximal possible value for the id param in the class "vertex" /!\ .
    int* dfs_number;
    int* lowlink;
    int* component;
    bool* waiting;
    std::stack<int> stack_; // for the points that were reached during the search but were not yet placed in any component
    void StrongConnect(vertex* v, int& i, int& component_numb);
    void ComputeStrongConnectedComponents();
};