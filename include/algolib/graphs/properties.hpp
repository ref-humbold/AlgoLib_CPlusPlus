/*!
 * \file properties.hpp
 * \brief Structure of graph properties.
 */
#ifndef PROPERTIES_HPP_
#define PROPERTIES_HPP_

#include <limits>

namespace algolib::graphs
{
    struct weighted
    {
        using weight_type = double;

        virtual ~weighted() = default;

        virtual const weight_type & weight() const = 0;

        static constexpr weight_type infinity = std::numeric_limits<double>::infinity();
    };
}

#endif
