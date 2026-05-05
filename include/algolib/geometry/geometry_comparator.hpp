#ifndef GEOMETRY_COMPARATOR_HPP_
#define GEOMETRY_COMPARATOR_HPP_

#include <cmath>

namespace algolib::geometry
{
    class geometry_comparator
    {
    public:
        static int compare(double d1, double d2)
        {
            return std::abs(d1 - d2) < epsilon ? 0 : d1 < d2 ? -1 : 1;
        }

    private:
        static constexpr double epsilon = 1e-12;
    };
}

#endif
