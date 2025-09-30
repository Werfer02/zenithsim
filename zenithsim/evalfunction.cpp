#include "evalfunction.hpp"

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
