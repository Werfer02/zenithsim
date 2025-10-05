#include "node.hpp"

#include <iostream>

namespace zenithsim {

std::vector<bool> node::evaluate() const{
    std::vector<bool> inputs;
    for(auto i : connections){

        inputs.push_back(i.targetnode->evaluate()[i.outputidx]);

    }
    return (*evalfunc)(inputs);
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

std::shared_ptr<node> node::create(const evalfunction& e){

    return std::make_shared<node>(e);

}

std::shared_ptr<node> node::create(const evalfunction& e, const std::vector<connection>& c){

    return std::make_shared<node>(e, c);
    
}

void node::addconnection(const connection& c){
    connections.push_back(c);
}

void node::setconnection(const connection& c, int idx){
    if(!(idx < connections.size())) std::cerr << "no such input: " << idx << ", connections.size(): " << connections.size();
    connections[idx] = c;
}

std::vector<connection> node::getconnections() const{
    return connections;
}
void node::setconnections(const std::vector<connection>& inconnections){
    connections = inconnections;
}

std::shared_ptr<evalfunction> node::getevalfunc() const {
    return evalfunc;
}

void node::setevalfunc(std::shared_ptr<evalfunction> ef) { 
    evalfunc = ef; 
}

int node::idcounter = 0;

int node::getid() const{
    return id;
}

}