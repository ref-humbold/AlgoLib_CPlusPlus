#ifndef GEOMETRY_COMPARATOR_HPP_
#define GEOMETRY_COMPARATOR_HPP_

#include <cmath>

namespace algolib::geometry
{
    class geometry_comparator
    {
    public:
        static std::weak_ordering compare(double d1, double d2)
        {
            return std::abs(d1 - d2) < epsilon ? std::weak_ordering::equivalent
                    : d1 < d2                  ? std::weak_ordering::less
                                               : std::weak_ordering::greater;
        }

    private:
        static constexpr double epsilon = 1e-12;
    };
}

#endif
