/**!
 * \file maximum_subarray.hpp
 * \brief Algorithms for maximum subarray
 */
#ifndef MAXIMUM_SUBARRAY_HPP_
#define MAXIMUM_SUBARRAY_HPP_

#include <cstdlib>
#include <algorithm>
#include <functional>
#include <optional>
#include <vector>

namespace algolib::sequences
{
    /*!
     * \brief Dynamically constructs coherent subarray with maximal sum.
     * \param sequence the sequence of numbers
     * \return the maximum subarray
     */
    std::vector<double> find_maximum_subarray(const std::vector<double> & sequence);

    /*!
     * \brief Computes maximal sum from all coherent subarrays using interval tree.
     * \param sequence the sequence of numbers
     * \return the sum of maximum subarray
     */
    double count_maximal_subsum(const std::vector<double> & sequence);
}

#endif
