#ifndef GEOMETRY_OBJECT_HPP_
#define GEOMETRY_OBJECT_HPP_

#include <cmath>
#include <array>

namespace algolib::geometry
{
    template <size_t N>
    class geometry_object
    {
    public:
        virtual ~geometry_object() = default;

        virtual std::array<double, N> coordinates() const = 0;

        static constexpr double epsilon = 1e-12;

    protected:
        static bool equal(double d1, double d2)
        {
            return std::abs(d1 - d2) < epsilon;
        }
    };
}

#endif
