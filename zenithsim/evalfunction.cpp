#include "evalfunction.hpp"

bool alwaysTrueEval(const std::vector<bool>&){ return true; }
bool alwaysFalseEval(const std::vector<bool>&){ return false; }

bool ANDEval(const std::vector<bool>& inputs){
    for(bool i : inputs){ if(!i) return false; }
    return true;
}

bool OREval(const std::vector<bool>& inputs){
    for(bool i : inputs){ if(i) return true; }
    return false;
}

bool NOTEval(const std::vector<bool>& inputs){
    return !inputs[0];
}

bool XOREval(const std::vector<bool>& inputs){
    bool current = false;
    for(bool i : inputs){ current = (current != i); }
    return current;
}
