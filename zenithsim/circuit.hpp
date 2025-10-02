#pragma once

#include "node.hpp"

class Circuit {

    std::vector<std::shared_ptr<node>> inputnodes;
    std::vector<std::shared_ptr<node>> outputnodes;
    
public:
    Circuit(std::vector<std::shared_ptr<node>> inputnodesin, std::vector<std::shared_ptr<node>> outputnodesin) : 
    inputnodes(inputnodesin), outputnodes(outputnodesin) {};

    void switchinput(const int&);
    void setinput(const int&, const bool&);
    void setinputs(const std::vector<bool>&);
    std::vector<bool> evaloutputs() const;
    std::vector<bool> evaloutputs(const std::vector<bool>&);
    evalfunction genevalfunction();

    friend std::ostream& operator<<(std::ostream&, const Circuit&);

};