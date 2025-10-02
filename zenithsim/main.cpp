#include <iostream>
#include <memory>
#include <vector>

#include "evalfunction.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "clutils.hpp"

int main(){

    auto Node1 = node::create(TRUE);
    auto Node2 = node::create(TRUE);
    auto Node3 = node::create(FALSE);
    auto Node4 = node::create(FALSE);

    auto Node5 = node::create(AND, {Node1, Node2});
    auto Node6 = node::create(AND, {Node3, Node4});

    auto Node7 = node::create(XOR, {Node5, Node6});

    std::cout << Node1 << "\n";
    std::cout << Node2 << "\n";
    std::cout << Node3 << "\n";
    std::cout << Node4 << "\n";
    std::cout << Node5 << "\n";
    std::cout << Node6 << "\n";
    std::cout << Node7 << "\n";

    Circuit Circuit1({Node1, Node2, Node3, Node4}, {Node7});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 0, 0, 0});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 1, 1, 1});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 0, 1, 0});
    std::cout << Circuit1 << "\n";

    auto Node8 = node::create(TRUE);
    auto Node9 = node::create(FALSE);
    auto Node10 = node::create(Circuit1.genevalfunction(), {Node8, Node9});

}