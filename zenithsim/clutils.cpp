#include <clutils.hpp>

std::ostream& operator<<(std::ostream& os, const node& n){
    os << "Node " << &n << ":\ndepth: " << n.getdepth() << "\neval:";
    for(auto i : n.evaluate()){
        os << i;
    }
    os << "\nconnections:\n";
    for(auto i : n.connections){
        os << i.targetnode.get() << "\n";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n){ os << *n; return os; }
