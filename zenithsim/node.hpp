#pragma once

#include <memory>
#include "evalfunction.hpp"

struct node;

struct connection{
    std::shared_ptr<node> targetnode;
    size_t outputidx;
    connection(std::shared_ptr<node> n, size_t idx = 0) : targetnode(n), outputidx(idx) {}
};

struct node{

    std::vector<connection> connections;
    eval evalfunc;

    node(eval inevalfunc) : evalfunc(inevalfunc) {}
    node(eval inevalfunc, std::vector<connection> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    static std::shared_ptr<node> create(const eval&);
    static std::shared_ptr<node> create(const eval&, const std::vector<connection>&);

    std::vector<bool> evaluate() const;
    int getdepth() const;

};

