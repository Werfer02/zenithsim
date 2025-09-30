#include "node.hpp"
#include "evalfunction.hpp"

bool node::evaluate(){
    std::vector<bool> inputs;
    for(auto i : connections){

        inputs.push_back(i->evaluate());

    }
    return evalfunc(inputs);
}