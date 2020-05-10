#include<iostream>
#include<unordered_set>
#include<stack>
#include<vector>
#include<unordered_map>
#include<cmath>
#include<string>

class vertex {
public:
    vertex() {
        number = -1;
        lowlink = -1;
        component = -1;
        waiting = false;
    }
    int number;
    int lowlink;
    int component;
    bool waiting;
    std::string name;
}; 

std::vector<vertex> VertexList;

std::unordered_map<vertex*, std::unordered_set<vertex*> > graph;

std::stack<vertex*> stack_; // for the points that were reached during the search but were not yet placed in any component

void StrongConnect(vertex* v, int& i, int& component_numb)
{
    i++;
    v->number = i;std::cout << "vector " << v->number << std::endl;
    v->lowlink = i;
    stack_.push(v);
    v->waiting = true;
    for (auto w : graph[v]) {
        if(w->number == -1)
        {
            StrongConnect(w, i, component_numb);
            v->lowlink = std::min(v->lowlink, w->lowlink);
        }
        else if(w->number < v->number && w->waiting)
        {
            v->lowlink = std::min(v->lowlink, w->number);
        }
    }

    if(v->lowlink == v->number) // if v is the root of a strongly connected component
    {
        std::cout << "chegou aqui e a stack tem " << stack_.size() << " elementos" << std::endl;
        component_numb++; // start new component
        while(!stack_.empty() && stack_.top()->number >= v->number)
        {
            stack_.top()->component = component_numb;
            std::cout << "vector " << stack_.top()->number << " belongs to component " << stack_.top()->component << std::endl;
            stack_.top()->waiting = false;
            stack_.pop();
        }
        std::cout << "saiu daqui" << std::endl;
    }
}

void ComputeStrongConnectedComponents()
{
    int i = 0;
    int component_numb = 0;
    while(!stack_.empty()) stack_.pop();
    for(auto elem : graph)
    {
        vertex* v = elem.first;
        if(v->number == -1) StrongConnect(v, i, component_numb);
    }
}

int main()
{
    vertex v1, v2, v3, v4, v5, v6, v7, v8;
    v1.name = "A";
    v2.name = "B";
    v3.name = "C";
    v4.name = "D";
    v5.name = "E";
    v6.name = "F";
    v7.name = "G";
    v8.name = "H";

    std::unordered_set<vertex*> set_;
    set_.insert(&v2);
    graph[&v1] = set_;

    set_.clear();
    set_.insert(&v3);
    set_.insert(&v8);
    graph[&v2] = set_;
    
    set_.clear();
    set_.insert(&v4);
    set_.insert(&v7);
    graph[&v3] = set_;

    set_.clear();
    set_.insert(&v5);
    graph[&v4] = set_;

    set_.clear();
    set_.insert(&v3);
    set_.insert(&v6);
    graph[&v5] = set_;

    set_.clear();
    graph[&v6] = set_;

    set_.clear();
    set_.insert(&v4);
    set_.insert(&v6);
    graph[&v7] = set_;

    set_.clear();
    set_.insert(&v1);
    set_.insert(&v7);
    graph[&v8] = set_;

    std::cout << "number of neighbours per vertex: \n";
    for(auto elem : graph)
    {
        std::cout << elem.second.size() << std::endl;
    }
    
    ComputeStrongConnectedComponents();

    for(auto elem : graph)
    {
        std::cout << elem.first->name << " " << elem.first->component << std::endl;
    }

    return 0;
}