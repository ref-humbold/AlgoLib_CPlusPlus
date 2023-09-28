/*!
 * \file sorting.hpp
 * \brief Algorithms for sorting vectors
 */
#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include <vector>

namespace internal
{
    // Randomly chooses pivot for quick-sort algorithm.
    size_t choose_pivot(
            std::uniform_int_distribution<size_t> & distribution,
            std::default_random_engine & rand_eng);

    void validate_indices(size_t size, size_t index_begin, size_t index_end);

    // Move element down inside given heap.
    template <typename T>
    void move_down(std::vector<T> & heap, size_t vertex, size_t index_begin, size_t index_end)
    {
        size_t next_vertex = std::numeric_limits<size_t>::max();
        size_t left_vertex = vertex + vertex - index_begin + 1;
        size_t right_vertex = vertex + vertex - index_begin + 2;

        if(right_vertex < index_end)
            next_vertex = heap[right_vertex] < heap[left_vertex] ? left_vertex : right_vertex;

        if(left_vertex == index_end - 1)
            next_vertex = left_vertex;

        if(next_vertex == std::numeric_limits<size_t>::max())
            return;

        if(heap[next_vertex] > heap[vertex])
            std::swap(heap[next_vertex], heap[vertex]);

        move_down(heap, next_vertex, index_begin, index_end);
    }

    // Merges two sorted fragments of given sequence. Guaranteed to be stable.
    template <typename T>
    void merge(std::vector<T> & sequence, size_t index_begin, size_t index_middle, size_t index_end)
    {
        std::vector<T> ordered;
        size_t iter1 = index_begin, iter2 = index_middle;

        while(iter1 < index_middle && iter2 < index_end)
            if(sequence[iter1] < sequence[iter2])
            {
                ordered.push_back(sequence[iter1]);
                ++iter1;
            }
            else
            {
                ordered.push_back(sequence[iter2]);
                ++iter2;
            }

        for(size_t i = iter1; i < index_middle; ++i)
            ordered.push_back(sequence[i]);

        for(size_t i = iter2; i < index_end; ++i)
            ordered.push_back(sequence[i]);

        for(size_t i = 0; i < ordered.size(); ++i)
            sequence[index_begin + i] = ordered[i];
    }

    // Mutably sorts given sequence using recursive merge-sort algorithm.
    template <typename T>
    void do_merge_sort(std::vector<T> & sequence, size_t index_begin, size_t index_end)
    {
        if(index_end - index_begin <= 1)
            return;

        size_t index_middle = (index_begin + index_end) / 2;

        do_merge_sort(sequence, index_begin, index_middle);
        do_merge_sort(sequence, index_middle, index_end);
        internal::merge(sequence, index_begin, index_middle, index_end);
    }

    // Mutably sorts given sequence using quick-sort algorithm.
    template <typename T>
    void do_quick_sort(
            std::default_random_engine & rand_eng,
            std::vector<T> & sequence,
            size_t index_begin,
            size_t index_end)
    {
        if(index_end - index_begin <= 1)
            return;

        std::uniform_int_distribution<size_t> distribution(index_begin, index_end - 1);
        size_t index_pivot = index_begin, index_front = index_begin + 1, index_back = index_end - 1;
        size_t random_pivot = internal::choose_pivot(distribution, rand_eng);

        std::swap(sequence[index_pivot], sequence[random_pivot]);

        while(index_pivot < index_back)
            if(sequence[index_front] < sequence[index_pivot])
            {
                std::swap(sequence[index_front], sequence[index_pivot]);
                index_pivot = index_front;
                ++index_front;
            }
            else
            {
                std::swap(sequence[index_front], sequence[index_back]);
                --index_back;
            }

        do_quick_sort(rand_eng, sequence, index_begin, index_pivot);
        do_quick_sort(rand_eng, sequence, index_pivot + 1, index_end);
    }
}

namespace algolib::sequences
{
    /*!
     * \brief Mutably sorts given sequence using heap.
     * \tparam T the type of sequence elements
     * \param sequence the sequence of elements
     * \param index_begin the index of sequence beginning
     * \param index_end the index of sequence end
     */
    template <typename T>
    void heap_sort(
            std::vector<T> & sequence,
            size_t index_begin = 0,
            size_t index_end = std::numeric_limits<size_t>::max())
    {
        if(index_end == std::numeric_limits<size_t>::max())
            index_end = sequence.size();

        internal::validate_indices(sequence.size(), index_begin, index_end);

        size_t heap_size = index_end - index_begin;

        if(heap_size <= 1)
            return;

        for(size_t i = 1 + index_begin + heap_size / 2; i > index_begin; --i)
            internal::move_down(sequence, i - 1, index_begin, index_end);

        while(heap_size > 1)
        {
            size_t index_heap = index_begin + heap_size - 1;

            std::swap(sequence[index_heap], sequence[index_begin]);
            internal::move_down(sequence, index_begin, index_begin, index_heap);
            --heap_size;
        }
    }

    /*!
     * \brief Mutably sorts given sequence using top-down merge-sort algorithm.
     * \tparam T the type of sequence elements
     * \param sequence the sequence of elements
     * \param index_begin the index of sequence beginning
     * \param index_end the index of sequence end
     */
    template <typename T>
    void top_down_merge_sort(
            std::vector<T> & sequence,
            size_t index_begin = 0,
            size_t index_end = std::numeric_limits<size_t>::max())
    {
        if(index_end == std::numeric_limits<size_t>::max())
            index_end = sequence.size();

        internal::validate_indices(sequence.size(), index_begin, index_end);
        internal::do_merge_sort(sequence, index_begin, index_end);
    }

    /*!
     * \brief Mutably sorts given sequence using bottom-up merge-sort algorithm.
     * \tparam T the type of sequence elements
     * \param sequence the sequence of elements
     * \param index_begin the index of sequence beginning
     * \param index_end the index of sequence end
     */
    template <typename T>
    void bottom_up_merge_sort(
            std::vector<T> & sequence,
            size_t index_begin = 0,
            size_t index_end = std::numeric_limits<size_t>::max())
    {
        if(index_end == std::numeric_limits<size_t>::max())
            index_end = sequence.size();

        internal::validate_indices(sequence.size(), index_begin, index_end);

        if(index_end - index_begin <= 1)
            return;

        for(size_t half_step = 2; half_step < 2 * (index_end - index_begin); half_step *= 2)
            for(size_t i = index_begin; i < index_end; i += half_step)
                internal::merge(
                        sequence, i, std::min(i + half_step / 2, index_end),
                        std::min(i + half_step, index_end));
    }

    /*!
     * \brief Mutably sorts given sequence using quick-sort algorithm.
     * \tparam T the type of sequence elements
     * \param sequence the sequence of elements
     * \param index_begin the index of sequence beginning
     * \param index_end the index of sequence end
     */
    template <typename T>
    void quick_sort(
            std::vector<T> & sequence,
            size_t index_begin = 0,
            size_t index_end = std::numeric_limits<size_t>::max())
    {
        std::default_random_engine rand_eng;

        if(index_end == std::numeric_limits<size_t>::max())
            index_end = sequence.size();

        internal::validate_indices(sequence.size(), index_begin, index_end);
        internal::do_quick_sort(rand_eng, sequence, index_begin, index_end);
    }
}

#endif
