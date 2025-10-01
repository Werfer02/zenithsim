#pragma once

#include <iostream>

#include "node.hpp"

std::ostream& operator<<(std::ostream& os, const node& n);

std::ostream& operator<<(std::ostream& os, const std::shared_ptr<node>& n);

std::string nodestable(const std::vector<std::shared_ptr<node>>& nodes);
