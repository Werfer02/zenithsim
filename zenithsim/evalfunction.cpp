#include "evalfunction.hpp"

namespace zenithsim {

std::vector<bool> alwaysTrueEval(const std::vector<bool>&){ return {true}; }
std::vector<bool> alwaysFalseEval(const std::vector<bool>&){ return {false}; }

std::vector<bool> ANDEval(const std::vector<bool>& inputs){
    for(bool i : inputs){ if(!i) return {false}; }
    return {true};
}

std::vector<bool> OREval(const std::vector<bool>& inputs){
    for(bool i : inputs){ if(i) return {true}; }
    return {false};
}

std::vector<bool> NOTEval(const std::vector<bool>& inputs){
    return {!inputs[0]};
}

std::vector<bool> XOREval(const std::vector<bool>& inputs){
    bool current = false;
    for(bool i : inputs){ current = (current != i); }
    return {current};
}

size_t evalfunctionhash::operator()(const evalfunction& f) const{
    if (auto p = f.target<bool(*)(std::vector<bool>)>()) {
        return reinterpret_cast<size_t>(p); // if static function
    }
    return reinterpret_cast<size_t>(f.target<void()>()); // if lambda or other
}

bool evalfunctionequal::operator()(const evalfunction& f1, const evalfunction& f2) const {
    return f1.target<bool(*)(const std::vector<bool>&)>() == f2.target<bool(*)(const std::vector<bool>&)>();
}

std::unordered_map<eval, evalfunction> evalfunctionmap {
    {eval::TRUE,  alwaysTrueEval},
    {eval::FALSE, alwaysFalseEval},
    {eval::AND,   ANDEval},
    {eval::OR,    OREval},
    {eval::NOT,   NOTEval},
    {eval::XOR,   XOREval}
};

std::unordered_map<evalfunction, eval, evalfunctionhash, evalfunctionequal> evalmap {
    {alwaysTrueEval,  eval::TRUE},
    {alwaysFalseEval, eval::FALSE},
    {ANDEval,         eval::AND},
    {OREval,          eval::OR},
    {NOTEval,         eval::NOT},
    {XOREval,         eval::XOR}
};

}
