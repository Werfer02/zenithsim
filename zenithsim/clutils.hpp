#pragma once

#include <iostream>

#include "node.hpp"
#include "circuit.hpp"

std::ostream& operator<<(std::ostream& os, const node& n);

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n);

std::ostream& operator<<(std::ostream& os, const Circuit& c);
