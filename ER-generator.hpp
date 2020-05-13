#include"vertex.hpp"
#include"graph.hpp"

class ERGenerator : public graph {
public:
    ERGenerator(int n, double prob);
    ~ERGenerator();
};