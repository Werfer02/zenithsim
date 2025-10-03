#include <clutils.hpp>

#include "node.hpp"
#include "circuit.hpp"

namespace zenithsim {

std::ostream& operator<<(std::ostream& os, const node& n){
    os << "Node " << n.getid() << ":\ndepth: " << n.getdepth() << "\nconnections:\n";
    for(auto i : n.connections){
        os << "Node " << i.targetnode->getid() << ", eval: " << i.targetnode->evaluate()[i.outputidx] << "\n";
    }
    os << "eval:\n";
    for(auto i : n.evaluate()){
        os << i << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n){ os << *n; return os; }

std::ostream& operator<<(std::ostream& os, const Circuit& c){
    os << "Circuit " << &c << ":\ninputs:\n";
    for(auto i : c.inputnodes){
        os << "Node " << i->getid() << ", eval: " << i->evaluate()[0] << "\n";
    }
    os << "outputs:\n";
    for(auto i : c.outputnodes){
        os << "Node " << i.targetnode->getid() << ", eval: " << i.targetnode->evaluate()[i.outputidx] << "\n";
    }
    return os;
}

}
