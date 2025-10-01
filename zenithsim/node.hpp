#pragma once

#include <memory>
#include "evalfunction.hpp"

struct node{

    std::vector<std::shared_ptr<node>> connections;
    eval evalfunc;

    node(eval inevalfunc, std::vector<std::shared_ptr<node>> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    node(eval inevalfunc) : evalfunc(inevalfunc) {}

    static node create();

    bool evaluate() const;
    int getdepth() const;

};

