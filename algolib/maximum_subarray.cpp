// ALGORYTMY WYZNACZANIA PODCIĄGU SPÓJNEGO O MAKSYMALNEJ SUMIE
#include "maximum_subarray.hpp"

std::vector<double> algolib::find_maxsum_subseq1(const std::vector<double> & sequence)
{
    std::vector<double> max_subseq, actual_subseq;
    double max_sum = 0.0, actual_sum = 0.0;

    for(const auto & elem : sequence)
    {
        if(actual_sum < 0.0)
        {
            actual_sum = 0.0;
            actual_subseq.clear();
        }

        actual_subseq.push_back(elem);
        actual_sum += elem;

        if(actual_sum > max_sum)
        {
            max_sum = actual_sum;
            max_subseq = actual_subseq;
        }
    }

    return max_subseq;
}

double algolib::find_maxsum_subseq2(const std::vector<double> & sequence)
{
    size_t size = 1;

    while(size < 2 * sequence.size())
        size <<= 1;

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
        index >>= 1;

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
            index >>= 1;
        }
    }

    return interval_sums[1];
}
