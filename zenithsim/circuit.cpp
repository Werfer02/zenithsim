#include "circuit.hpp"

#include <iostream>

void Circuit::switchinput(int idx){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    inputnodes[idx]->evalfunc = (eval)!inputnodes[idx]->evalfunc; // thanks to FALSE = 0 and TRUE = 1

}

void Circuit::setinput(int idx, bool input){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    inputnodes[idx]->evalfunc = (eval)input; // again, thanks to FALSE = 0 and TRUE = 1

}