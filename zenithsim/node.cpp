#include "node.hpp"
#include "evalfunction.hpp"

std::vector<bool> node::evaluate() const{
    std::vector<bool> inputs;
    for(auto i : connections){

        inputs.push_back(i.targetnode->evaluate()[i.outputidx]);

    }
    return evalfunctionmap[evalfunc](inputs);
}

int node::getdepth() const{
    int depth = -1;
    for(auto i : connections){

        depth = std::max(depth, i.targetnode->getdepth());

    }
    return depth + 1;
}

std::shared_ptr<node> node::create(const eval& e){

    return std::make_shared<node>(e);

}

std::shared_ptr<node> node::create(const eval& e, const std::vector<connection>& c){

    return std::make_shared<node>(e, c);
    
}