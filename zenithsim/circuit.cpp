#include "circuit.hpp"

#include <iostream>

namespace zenithsim {

void Circuit::switchinput(const int& idx){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    evalfunction currentevalfunction = *inputnodes[idx]->getevalfunc();
    eval currenteval = evalmap[currentevalfunction];
    eval newEvalState = (eval)!(int)currenteval; // thanks to FALSE = 0 and TRUE = 1
    inputnodes[idx]->setevalfunc(std::make_shared<evalfunction>(evalfunctionmap[newEvalState]));

}

void Circuit::setinput(const int& idx, const bool& input){

    if(!(idx < inputnodes.size())) std::cerr << "no such input: " << idx << ", inputnodes.size(): " << inputnodes.size();
    inputnodes[idx]->setevalfunc(std::make_shared<evalfunction>(evalfunctionmap[(eval)input])); // again, thanks to FALSE = 0 and TRUE = 1

}

void Circuit::setinputs(const std::vector<bool>& inputs){
    for(int i = 0; i < inputnodes.size(); i++){

        inputnodes[i]->setevalfunc(std::make_shared<evalfunction>(evalfunctionmap[(eval)inputs[i]])); // again again

    }
}

std::vector<bool> Circuit::evaloutputs() const{
    std::vector<bool> outputs;
    for(auto i : outputnodes){

        outputs.push_back(i.targetnode->evaluate()[i.outputidx]);

    }
    return outputs;
}

std::vector<bool> Circuit::evaloutputs(const std::vector<bool>& inputs){
    setinputs(inputs);
    return evaloutputs();
}

evalfunction Circuit::genevalfunction(){

    std::vector<bool> inputs(inputnodes.size());
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

    int numinputs = inputs.size();
    evalfunction outputmapeval = [outputsmap, numinputs](const std::vector<bool>& inputsvector) -> std::vector<bool>{
        
        if(inputsvector.size() == numinputs) return outputsmap.at(inputsvector);
        return std::vector<bool>(1, false);

    };

    return outputmapeval;

}

}