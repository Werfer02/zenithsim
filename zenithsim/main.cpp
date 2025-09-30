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

}