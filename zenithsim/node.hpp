#pragma once

#include <memory>
#include "fwddecls.hpp"
#include "evalfunction.hpp"

namespace zenithsim {

struct connection{
    std::shared_ptr<node> targetnode;
    size_t outputidx;
    connection(std::shared_ptr<node> n, size_t idx = 0) : targetnode(n), outputidx(idx) {}
};

class node{

    std::vector<connection> connections;
    std::shared_ptr<evalfunction> evalfunc;
    static int idcounter;
    int id;

public:
    node(eval ineval) : evalfunc(std::make_shared<evalfunction>(evalfunctionmap[ineval])) { id = idcounter++; }
    node(evalfunction ineval) : evalfunc(std::make_shared<evalfunction>(ineval)) { id = idcounter++; }

    node(eval ineval, std::vector<connection> inconnections) : 
    evalfunc(std::make_shared<evalfunction>(evalfunctionmap[ineval])), connections(inconnections) { id = idcounter++; }
    node(evalfunction ineval, std::vector<connection> inconnections) : 
    evalfunc(std::make_shared<evalfunction>(ineval)), connections(inconnections) { id = idcounter++; }

    static std::shared_ptr<node> create(const eval&);
    static std::shared_ptr<node> create(const eval&, const std::vector<connection>&);
    static std::shared_ptr<node> create(const evalfunction&);
    static std::shared_ptr<node> create(const evalfunction&, const std::vector<connection>&);

    void addconnection(const connection&);

    void setconnection(const connection&, int idx);
    void setconnections(const std::vector<connection>&);

    std::shared_ptr<evalfunction> getevalfunc() const;
    void setevalfunc(std::shared_ptr<evalfunction>);

    int getid() const;

    std::vector<bool> evaluate() const;
    int getdepth() const;

    friend std::ostream& operator<<(std::ostream&, const node&);
    friend std::ostream& operator<<(std::ostream&, const Circuit&);

};

}