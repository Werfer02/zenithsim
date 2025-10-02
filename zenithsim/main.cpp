#include <iostream>
#include <memory>
#include <vector>

#include "evalfunction.hpp"
#include "node.hpp"
#include "clutils.hpp"

int main(){

    auto Node1 = node::create(TRUE);
    auto Node2 = node::create(FALSE);
    auto Node3 = node::create(TRUE);
    auto Node4 = node::create(FALSE);

    auto Node5 = node::create(AND, {Node1, Node2});
    auto Node6 = node::create(AND, {Node1, Node3});

    auto Node7 = node::create(XOR, {Node5, Node6});

    std::cout << Node1 << "\n";
    std::cout << Node2 << "\n";
    std::cout << Node3 << "\n";
    std::cout << Node4 << "\n";
    std::cout << Node5 << "\n";
    std::cout << Node6 << "\n";
    std::cout << Node7 << "\n";

}