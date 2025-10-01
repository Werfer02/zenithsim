#include "node.hpp"
#include "evalfunction.hpp"

bool node::evaluate(){
    std::vector<bool> inputs;
    for(auto i : connections){

        inputs.push_back(i->evaluate());

    }
    return evalfunc(inputs);
}

int node::getdepth(){
    int depth = -1;
    for(auto i : connections){

        if(i->getdepth() > depth) depth = i->getdepth();

    }
    return depth + 1;
}