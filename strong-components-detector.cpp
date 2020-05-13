#include"strong-components-detector.hpp"

StrongComponentDetector::StrongComponentDetector(int max_id, graph* graph_) {
    this->graph_ = graph_;
    this->max_id = max_id;
    dfs_number = new int[max_id+1];
    lowlink = new int[max_id+1];
    component = new int[max_id+1];
    waiting = new bool[max_id+1];
    for(int i = 0; i < max_id+1; i++)
    {
        dfs_number[i] = -1;
        lowlink[i] = -1;
        component[i] = -1;
        waiting[i] = false;
    }
}

StrongComponentDetector::~StrongComponentDetector() {
    delete[] dfs_number;
    delete[] lowlink;
    delete[] component;
    delete[] waiting;
}

void StrongComponentDetector::StrongConnect(vertex* v, int& i, int& component_numb)
{
    i++;
    dfs_number[v->id] = i;
    lowlink[v->id] = i;
    stack_.push(v->id);
    waiting[v->id] = true;
    for (auto w : graph_->EdgeList[v]) {
        if(dfs_number[w->id] == -1)
        {
            StrongConnect(w, i, component_numb);
            lowlink[v->id] = std::min(lowlink[v->id], lowlink[w->id]);
        }
        else if(dfs_number[w->id] < dfs_number[v->id] && waiting[w->id])
        {
            lowlink[v->id] = std::min(lowlink[v->id], dfs_number[w->id]);
        }
    }

    if(lowlink[v->id] == dfs_number[v->id]) // if v is the root of a strongly connected component
    {
        component_numb++; // start new component
        while(!stack_.empty() && dfs_number[stack_.top()] >= dfs_number[v->id])
        {
            component[stack_.top()] = component_numb;
            waiting[stack_.top()] = false;
            stack_.pop();
        }
    }
}

void StrongComponentDetector::ComputeStrongConnectedComponents()
{
    int i = 0;
    int component_numb = 0;
    while(!stack_.empty()) stack_.pop();
    for(auto elem : graph_->EdgeList)
    {
        vertex* v = elem.first;
        if(dfs_number[v->id] == -1) StrongConnect(v, i, component_numb);
    }
}