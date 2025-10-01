#pragma once

#include <iostream>

#include "node.hpp"
#include "evalfunction.hpp"

std::ostream& operator<<(std::ostream& os, const node& n){
    os << "Node " << &n << ":\ndepth: " << n.getdepth() << "\neval: " << n.evaluate() << "\nconnections:\n";
    for(auto i : n.connections){
        os << i.get() << "\n";
    }
    return os;
}
