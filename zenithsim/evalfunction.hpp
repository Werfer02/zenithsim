#pragma once

#include <vector>
#include <functional>

using evalfunction = std::function<bool(std::vector<bool>)>;

bool alwaysTrueEval(std::vector<bool>);
bool alwaysFalseEval(std::vector<bool>);

bool ANDEval(std::vector<bool> inputs);

bool OREval(std::vector<bool> inputs);

bool NOTEval(std::vector<bool> inputs);

bool XOREval(std::vector<bool> inputs);