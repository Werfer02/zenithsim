#pragma once

#include <memory>
#include "evalfunction.hpp"

struct node{

    std::vector<std::shared_ptr<node>> connections;
    eval evalfunc;

    node(eval inevalfunc) : evalfunc(inevalfunc) {}
    node(eval inevalfunc, std::vector<std::shared_ptr<node>> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    static std::shared_ptr<node> create(const eval&);
    static std::shared_ptr<node> create(const eval&, const std::vector<std::shared_ptr<node>>&);

    bool evaluate() const;
    int getdepth() const;

};

