#include "circuit.hpp"

#include <iostream>

void Circuit::switchinput(const int& idx){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    inputnodes[idx]->evalfunc = (eval)!inputnodes[idx]->evalfunc; // thanks to FALSE = 0 and TRUE = 1

}

void Circuit::setinput(const int& idx, const bool& input){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    inputnodes[idx]->evalfunc = (eval)input; // again, thanks to FALSE = 0 and TRUE = 1

}

void Circuit::setinputs(const std::vector<bool>& inputs){
    for(int i = 0; i < inputnodes.size(); i++){

        inputnodes[i]->evalfunc = (eval)inputs[i]; // again again

    }
}

std::vector<bool> Circuit::evaloutputs(){
    std::vector<bool> outputs;
    for(auto i : outputnodes){

        outputs.push_back(i->evaluate()[0]);

    }
    return outputs;
}

std::vector<bool> Circuit::evaloutputs(const std::vector<bool>& inputs){
    setinputs(inputs);
    return evaloutputs();
}

evalfunction Circuit::genevalfunction(){

    std::vector<bool> inputs;
    std::vector<bool> outputs;
    std::unordered_map<std::vector<bool>, std::vector<bool>> outputsmap;
    int combinations = 1 << inputnodes.size();
    for(int i = 0; i < combinations; ++i) { // for each possible combination (digits are in i)

        for(int j = 0; j < inputnodes.size(); ++j) { // for each digit in the combination

            inputs[j] = (i & (1 << j)); // get the digit by ANDing 1 << j and i 

        }
        outputs = evaloutputs(inputs);
        outputsmap.insert({inputs, outputs});
    }

    evalfunction outputmapeval = [outputsmap](const std::vector<bool>& inputsvector) -> std::vector<bool>{

        return outputsmap.at(inputsvector);

    };

    return outputmapeval;

}