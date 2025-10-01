#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

using evalfunction = std::function<bool(const std::vector<bool>&)>;

bool alwaysTrueEval(const std::vector<bool>&);
bool alwaysFalseEval(const std::vector<bool>&);

bool ANDEval(const std::vector<bool>& inputs);

bool OREval(const std::vector<bool>& inputs);

bool NOTEval(const std::vector<bool>& inputs);

bool XOREval(const std::vector<bool>& inputs);

enum eval {
    FALSE = 0,
    TRUE = 1,
    AND,
    OR,
    NOT,
    XOR
};

std::unordered_map<eval, evalfunction> evalfunctionmap {
    {TRUE,  alwaysTrueEval},
    {FALSE, alwaysFalseEval},
    {AND,   ANDEval},
    {OR,    OREval},
    {NOT,   NOTEval},
    {XOR,   XOREval}
};

std::unordered_map<evalfunction, eval> evalmap {
    {alwaysTrueEval,  TRUE},
    {alwaysFalseEval, FALSE},
    {ANDEval,         AND},
    {OREval,          OR},
    {NOTEval,         NOT},
    {XOREval,         XOR}
};
