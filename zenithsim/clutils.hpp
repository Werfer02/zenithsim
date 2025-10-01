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

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n){ os << *n; return os; }

std::string nodestable(const std::vector<std::shared_ptr<node>>& nodes){
    node n(alwaysFalseEval, nodes);
    std::vector<std::vector<std::shared_ptr<node>>> columns(n.getdepth());

    int maxrows = 0;
    for (auto i : nodes) {
        int depth = i->getdepth();
        columns[depth].push_back(i);
        maxrows = std::max(maxrows, static_cast<int>(columns[depth].size()));
    }

    std::string table;
    for(int i = 0; i < maxrows; i++){
        for(int j = 0; j < columns.size(); j++){
            if (i < columns[j].size()) { table += std::to_string(columns[j][i]->evaluate()) + " "; }
            else { table += " "; }
        }
        table += "\n";
    }
    return table;
}
