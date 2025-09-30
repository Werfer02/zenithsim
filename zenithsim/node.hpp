#pragma once

#include <memory>
#include "evalfunction.hpp"

struct node{

    std::vector<std::shared_ptr<node>> connections;
    evalfunction evalfunc;

    node(evalfunction inevalfunc, std::vector<std::shared_ptr<node>> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    node(evalfunction inevalfunc) : evalfunc(inevalfunc) {}

    bool evaluate();
};