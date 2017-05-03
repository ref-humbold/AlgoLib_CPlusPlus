// SPEŁNIALNOŚĆ FORMUŁ 2-CNF
#ifndef TWOSAT_HPP
#define TWOSAT_HPP

#include <cstdlib>
#include <vector>
#include <algorithm>

using literal_type = int;

namespace algolib
{
    std::vector<bool> two_sat(std::vector<std::pair<literal_type, literal_type>> clauses);
}

#endif
