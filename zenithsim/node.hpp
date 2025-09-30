#include <memory>
#include "evalfunction.hpp"

struct node{

    node(evalfunction inevalfunc, std::vector<std::shared_ptr<node>> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    node(evalfunction inevalfunc) : evalfunc(inevalfunc) {}

    std::vector<std::shared_ptr<node>> connections;
    evalfunction evalfunc;

    bool evaluate(){
        std::vector<bool> inputs;
        for(auto i : connections){

            inputs.push_back(i->evaluate());

        }
        return evalfunc(inputs);
    }

};