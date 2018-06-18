// ALGORYTMY WYZNACZANIA PODCIĄGU SPÓJNEGO O MAKSYMALNEJ SUMIE
#include "algolib/maximum_subarray.hpp"

std::vector<double> algolib::find_maximum_subarray(const std::vector<double> & sequence)
{
    std::pair<double, std::vector<double>> actual, maximal;

    actual.first = 0.0;
    maximal.first = 0.0;

    for(const auto & elem : sequence)
    {
        if(actual.first < 0.0)
        {
            actual.first = 0.0;
            actual.second.clear();
        }

        actual.first += elem;
        actual.second.push_back(elem);

        if(actual.first > maximal.first)
        {
            maximal.first = actual.first;
            maximal.second = actual.second;
        }
    }

    return maximal.second;
}

double algolib::find_maximal_sum(const std::vector<double> & sequence)
{
    size_t size = 1;

    while(size < 2 * sequence.size())
        size *= 2;

    std::vector<double> interval_sums(size, 0.0);
    std::vector<double> prefix_sums(size, 0.0);
    std::vector<double> suffix_sums(size, 0.0);
    std::vector<double> all_sums(size, 0.0);

    for(size_t i = 0; i < sequence.size(); ++i)
    {
        int index = size / 2 + i;

        all_sums[index] += sequence[i];
        interval_sums[index] = std::max(all_sums[index], 0.0);
        prefix_sums[index] = std::max(all_sums[index], 0.0);
        suffix_sums[index] = std::max(all_sums[index], 0.0);
        index /= 2;

        while(index > 0)
        {
            int index_left = index + index, index_right = index + index + 1;

            interval_sums[index] =
                std::max(std::max(interval_sums[index_right], interval_sums[index_left]),
                         suffix_sums[index_right] + prefix_sums[index_left]);
            prefix_sums[index] =
                std::max(prefix_sums[index_right], all_sums[index_right] + prefix_sums[index_left]);
            suffix_sums[index] =
                std::max(suffix_sums[index_left], suffix_sums[index_right] + all_sums[index_left]);
            all_sums[index] = all_sums[index_right] + all_sums[index_left];
            index /= 2;
        }
    }

    return interval_sums[1];
}
