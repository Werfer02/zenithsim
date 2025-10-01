#pragma once

#include <vector>
#include <functional>
#include <unordered_map>

using evalfunction = std::function<bool(std::vector<bool>)>;

bool alwaysTrueEval(std::vector<bool>);
bool alwaysFalseEval(std::vector<bool>);

bool ANDEval(std::vector<bool> inputs);

bool OREval(std::vector<bool> inputs);

bool NOTEval(std::vector<bool> inputs);

bool XOREval(std::vector<bool> inputs);

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

std::unordered_map<bool(*)(std::vector<bool>), eval> evalmap {
    {alwaysTrueEval,  TRUE},
    {alwaysFalseEval, FALSE},
    {ANDEval,         AND},
    {OREval,          OR},
    {NOTEval,         NOT},
    {XOREval,         XOR}
};
