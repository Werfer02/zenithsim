#pragma once

#include "node.hpp"

class Circuit {

    Circuit();
    std::vector<std::shared_ptr<node>> inputnodes;
    std::vector<std::shared_ptr<node>> outputnodes;

    void switchinput(const int&);
    void setinput(const int&, const bool&);
    std::vector<bool> evaloutputs();
    std::vector<bool> evaloutputs(const std::vector<bool>&);
    evalfunction genevalfunction();

};