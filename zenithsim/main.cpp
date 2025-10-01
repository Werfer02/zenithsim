#include <iostream>
#include <memory>
#include <vector>

#include "evalfunction.hpp"
#include "node.hpp"

int main(){

    auto Node1 = std::make_shared<node>(alwaysTrueEval);
    auto Node2 = std::make_shared<node>(alwaysFalseEval);
    auto Node3 = std::make_shared<node>(alwaysTrueEval);
    auto Node4 = std::make_shared<node>(alwaysFalseEval);

    auto Node5 = std::make_shared<node>(&ANDEval, std::vector<std::shared_ptr<node>>{Node1, Node2});
    auto Node6 = std::make_shared<node>(&ANDEval, std::vector<std::shared_ptr<node>>{Node1, Node3});



    std::cout << Node5->evaluate() << "\n";
    std::cout << Node6->evaluate() << "\n";

    std::cout << Node1->getdepth() << "\n";
    std::cout << Node2->getdepth() << "\n";
    std::cout << Node5->getdepth() << "\n";
    std::cout << Node6->getdepth() << "\n";

}