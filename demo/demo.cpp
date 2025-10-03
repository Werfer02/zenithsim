#include <iostream>
#include <memory>
#include <vector>

#include "evalfunction.hpp"
#include "node.hpp"
#include "circuit.hpp"
#include "clutils.hpp"

namespace zs = zenithsim;

int main(){

    auto Node1 = zs::node::create(zs::eval::TRUE);
    auto Node2 = zs::node::create(zs::eval::TRUE);
    auto Node3 = zs::node::create(zs::eval::FALSE);
    auto Node4 = zs::node::create(zs::eval::FALSE);

    auto Node5 = zs::node::create(zs::eval::AND, {Node1, Node2});
    auto Node6 = zs::node::create(zs::eval::AND, {Node3, Node4});

    auto Node7 = zs::node::create(zs::eval::XOR, {Node5, Node6});

    std::cout << Node1 << "\n";
    std::cout << Node2 << "\n";
    std::cout << Node3 << "\n";
    std::cout << Node4 << "\n";
    std::cout << Node5 << "\n";
    std::cout << Node6 << "\n";
    std::cout << Node7 << "\n";

    zs::Circuit Circuit1({Node1, Node2, Node3, Node4}, {Node7});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 0, 0, 0});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 1, 1, 1});
    std::cout << Circuit1 << "\n";

    Circuit1.setinputs({1, 0, 1, 0});
    std::cout << Circuit1 << "\n";

    auto Node8 = zs::node::create(zs::eval::TRUE);
    auto Node9 = zs::node::create(zs::eval::FALSE);
    auto Node10 = zs::node::create(Circuit1.genevalfunction(), {Node8, Node8, Node9, Node9});

    std::cout << Node10 << "\n";
    Node10->setconnections({Node8, Node9, Node9, Node9});
    std::cout << Node10 << "\n";
    Node10->setconnections({Node8, Node8, Node8, Node8});
    std::cout << Node10 << "\n";
    Node10->setconnections({Node8, Node9, Node8, Node9});
    std::cout << Node10 << "\n";

}