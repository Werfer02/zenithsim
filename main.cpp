#include <iostream>
#include <memory>
#include <vector>

using evalfunction = bool(*)(std::vector<bool>);

bool alwaysTrueEval(std::vector<bool>){ return true; }
bool alwaysFalseEval(std::vector<bool>){ return false; }

bool ANDEval(std::vector<bool> inputs){
    for(bool i : inputs){ if(!i) return false; }
    return true;
}

bool OREval(std::vector<bool> inputs){
    for(bool i : inputs){ if(i) return true; }
    return false;
}

bool NOTEval(std::vector<bool> inputs){
    return !inputs[0];
}

bool XOREval(std::vector<bool> inputs){
    bool current = false;
    for(bool i : inputs){ current = (current != i); }
    return current;
}


struct node{

    node(evalfunction inevalfunc, std::vector<std::shared_ptr<node>> inconnections) : 
    evalfunc(inevalfunc), connections(inconnections) {}

    node(evalfunction inevalfunc) : evalfunc(inevalfunc) {}

    std::vector<std::shared_ptr<node>> connections;
    evalfunction evalfunc;

    bool evaluate(){
        std::vector<bool> inputs;
        for(auto i : connections){

            inputs.push_back(i->evaluate());

        }
        return evalfunc(inputs);
    }

};

int main(){

    auto Node1 = std::make_shared<node>(alwaysTrueEval);
    auto Node2 = std::make_shared<node>(alwaysFalseEval);
    auto Node3 = std::make_shared<node>(alwaysTrueEval);
    auto Node4 = std::make_shared<node>(alwaysFalseEval);

    std::cout << Node1->evaluate();
    std::cout << Node2->evaluate();
    std::cout << Node3->evaluate();
    std::cout << Node4->evaluate();

}