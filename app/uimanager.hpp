#pragma once

#include "uifwddecls.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class uimanager{

    int nodewidth;
    std::vector<uinode> uinodes;
    std::unordered_map<std::shared_ptr<zs::node>, uinode> uinodemap;

public:
    void addnode(auto ineval, std::vector<zs::connection> connections = {}); // ineval can be of type zenithsim::eval or zenithsim::evalfunction

};

struct nodehash{
    size_t operator()(const std::shared_ptr<zs::node>& n) const;
};

struct nodeequal{
    bool operator()(const std::shared_ptr<zs::node>& n1, const std::shared_ptr<zs::node>& n2) const;
};