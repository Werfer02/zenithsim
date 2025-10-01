#pragma once

#include "node.hpp"

class Circuit {

    Circuit();
    std::vector<std::shared_ptr<node>> inputnodes;
    std::vector<std::shared_ptr<node>> outputnodes;

    void switchinput(int idx);
    void setinput(int idx, bool input);
    std::vector<bool> evaloutputs();
    std::vector<bool> evaloutputs(std::vector<bool> inputs);
    evalfunction genevalfunction();

};