#pragma once

#include <iostream>
#include "fwddecls.hpp"
#include "node.hpp"

namespace zenithsim{

std::ostream& operator<<(std::ostream& os, const node& n);

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n);

std::ostream& operator<<(std::ostream& os, const Circuit& c);

}
