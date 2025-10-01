#include "node.hpp"
#include "evalfunction.hpp"

bool node::evaluate() const{
    std::vector<bool> inputs;
    for(auto i : connections){

        inputs.push_back(i->evaluate());

    }
    return evalfunc(inputs);
}

int node::getdepth() const{
    int depth = -1;
    for(auto i : connections){

        depth = std::max(depth, i->getdepth());

    }
    return depth + 1;
}