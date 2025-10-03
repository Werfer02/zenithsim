#pragma once

#include <vector>
#include <memory>

#include "evalfunction.hpp"
#include "node.hpp"

namespace zenithsim {
    
class Circuit {

    std::vector<std::shared_ptr<node>> inputnodes;
    std::vector<connection> outputnodes;
    
public:
    Circuit(std::vector<std::shared_ptr<node>> inputnodesin, std::vector<connection> outputnodesin) : 
    inputnodes(inputnodesin), outputnodes(outputnodesin) {};

    void switchinput(const int&);
    void setinput(const int&, const bool&);
    void setinputs(const std::vector<bool>&);
    std::vector<bool> evaloutputs() const;
    std::vector<bool> evaloutputs(const std::vector<bool>&);
    evalfunction genevalfunction();

    friend std::ostream& operator<<(std::ostream&, const Circuit&);

};

}