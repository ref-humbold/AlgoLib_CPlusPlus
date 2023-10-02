/**!
 * \file edit distance.cpp
 * \brief Algorithms for edit distance.
 */
#include "algolib/text/edit_distance.hpp"

namespace alte = algolib::text;

double alte::count_levenshtein(
        const std::string & source,
        const std::string & destination,
        double insertion_cost,
        double deletion_cost,
        double substitution_cost)
{
    if(insertion_cost < 0 || deletion_cost < 0 || substitution_cost < 0)
        throw std::invalid_argument("Cost cannot be negative");

    std::vector<double> distance;

    for(size_t i = 0; i <= destination.size(); ++i)
        distance.push_back(i * insertion_cost);

    for(auto && element : source)
    {
        size_t previous_above = distance[0];

        distance[0] += deletion_cost;

        for(size_t i = 0; i < destination.size(); ++i)
        {
            size_t previous_diagonal = previous_above;

            previous_above = distance[i + 1];
            distance[i + 1] = element == destination[i]
                                      ? previous_diagonal
                                      : std::min(
                                              std::min(
                                                      previous_above + deletion_cost,
                                                      distance[i] + insertion_cost),
                                              previous_diagonal + substitution_cost);
        }
    }

    return distance.back();
}

double alte::count_lcs(
        const std::string & source,
        const std::string & destination,
        double insertion_cost,
        double deletion_cost)
{
    if(insertion_cost < 0 || deletion_cost < 0)
        throw std::invalid_argument("Cost cannot be negative");

    std::vector<double> distance;

    for(size_t i = 0; i <= destination.size(); ++i)
        distance.push_back(i * insertion_cost);

    for(auto && element : source)
    {
        size_t previous_above = distance[0];

        distance[0] += deletion_cost;

        for(size_t i = 0; i < destination.size(); ++i)
        {
            size_t previous_diagonal = previous_above;

            previous_above = distance[i + 1];
            distance[i + 1] = element == destination[i] ? previous_diagonal
                                                        : std::min(
                                                                previous_above + deletion_cost,
                                                                distance[i] + insertion_cost);
        }
    }

    return distance.back();
}

double alte::count_hamming(
        const std::string & source, const std::string & destination, double substitution_cost)
{
    if(substitution_cost < 0)
        throw std::invalid_argument("Cost cannot be negative");

    if(source.size() != destination.size())
        throw std::invalid_argument("Texts must have equal length");

    double distance = 0.0;

    for(size_t i = 0; i < source.size(); ++i)
        if(source[i] != destination[i])
            distance += substitution_cost;

    return distance;
}
