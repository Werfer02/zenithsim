#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

using evalfunction = std::function<std::vector<bool>(const std::vector<bool>&)>;

std::vector<bool> alwaysTrueEval(const std::vector<bool>&);
std::vector<bool> alwaysFalseEval(const std::vector<bool>&);

std::vector<bool> ANDEval(const std::vector<bool>& inputs);

std::vector<bool> OREval(const std::vector<bool>& inputs);

std::vector<bool> NOTEval(const std::vector<bool>& inputs);

std::vector<bool> XOREval(const std::vector<bool>& inputs);

enum eval {
    FALSE = 0,
    TRUE = 1,
    AND,
    OR,
    NOT,
    XOR
};

struct evalfunctionhash{
    size_t operator()(const evalfunction& f) const;
};

struct evalfunctionequal{
    bool operator()(const evalfunction& f1, const evalfunction& f2) const;
};

extern std::unordered_map<eval, evalfunction> evalfunctionmap;

extern std::unordered_map<evalfunction, eval, evalfunctionhash, evalfunctionequal> evalmap;
