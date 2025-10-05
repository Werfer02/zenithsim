#include "uimanager.hpp"

#include "uinode.hpp"
#include "node.hpp"

#include <typeinfo>
#include <iostream>

void uimanager::addnode(auto ineval, std::vector<zs::connection> connections){
    if (typeid(ineval) != typeid(zs::eval) && typeid(ineval) != typeid(zs::evalfunction)){
        std::cout << "invalid type passed to addnode()";
    }
    auto n = zs::node::create(ineval, connections);
    uinode uin(n);
    uinodes.push_back(uin);
    uinodemap.insert({n, uin});
}

size_t nodehash::operator()(const std::shared_ptr<zs::node>& n) const{
    return std::hash<int>{}(n->getid());
}

bool nodeequal::operator()(const std::shared_ptr<zs::node>& n1, const std::shared_ptr<zs::node>& n2) const{
    return n1->getid() == n2->getid();
}