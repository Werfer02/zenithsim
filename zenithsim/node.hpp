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
    std::shared_ptr<evalfunction> evalfunc;

    node(eval ineval) : evalfunc(std::make_shared<evalfunction>(evalfunctionmap[ineval])) {}
    node(evalfunction ineval) : evalfunc(std::make_shared<evalfunction>(ineval)) {}

    node(eval ineval, std::vector<connection> inconnections) : 
    evalfunc(std::make_shared<evalfunction>(evalfunctionmap[ineval])), connections(inconnections) {}
    node(evalfunction ineval, std::vector<connection> inconnections) : 
    evalfunc(std::make_shared<evalfunction>(ineval)), connections(inconnections) {}

    static std::shared_ptr<node> create(const eval&);
    static std::shared_ptr<node> create(const eval&, const std::vector<connection>&);
    static std::shared_ptr<node> create(const evalfunction&);
    static std::shared_ptr<node> create(const evalfunction&, const std::vector<connection>&);

    void addconnection(const connection&);
    void addconnection(const connection&, int idx);

    std::vector<bool> evaluate() const;
    int getdepth() const;

};

