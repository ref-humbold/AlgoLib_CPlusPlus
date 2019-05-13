/**
 * @file sorting.hpp
 * @brief Sorting algorithms.
 */
#ifndef SORTING_HPP_
#define SORTING_HPP_

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <vector>

using point2D_t = std::pair<double, double>;

namespace impl
{
    template <typename T>
    void move_down(std::vector<T> & heap, int vertex, int index_begin, int index_end)
    {
        int next_vertex = -1;
        int left_vertex = vertex + vertex - index_begin + 1;
        int right_vertex = vertex + vertex - index_begin + 2;

        if(right_vertex < index_end)
            next_vertex = heap[right_vertex] < heap[left_vertex] ? left_vertex : right_vertex;

        if(left_vertex == index_end - 1)
            next_vertex = left_vertex;

        if(next_vertex < 0)
            return;

        if(heap[next_vertex] > heap[vertex])
            std::swap(heap[next_vertex], heap[vertex]);

        move_down(heap, next_vertex, index_begin, index_end);
    }

    template <typename T>
    void merge(std::vector<T> & sequence, int index_begin, int index_middle, int index_end)
    {
        std::vector<T> ordered;
        int iter1 = index_begin, iter2 = index_middle;

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

        for(int i = iter1; i < index_middle; ++i)
            ordered.push_back(sequence[i]);

        for(int i = iter2; i < index_end; ++i)
            ordered.push_back(sequence[i]);

        for(int i = 0; i < ordered.size(); ++i)
            sequence[index_begin + i] = ordered[i];
    }

    int choose_pivot(int size);

    void validate_indices(int size, int index_begin, int index_end);
}

namespace algolib
{
    /**
     * Mutowalne sortowanie kątowe punktów na płaszczyźnie.
     * @param points lista punktów
     */
    void angle_sort(std::vector<point2D_t> & points);

    /**
     * Mutowalne sortowanie ciągu przez kopcowanie.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void heap_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        if(index_end == -1)
            index_end = sequence.size();

        impl::validate_indices(sequence.size(), index_begin, index_end);

        int heap_size = index_end - index_begin;

        if(heap_size <= 1)
            return;

        for(int i = index_begin + heap_size / 2; i >= index_begin; --i)
            impl::move_down(sequence, i, index_begin, index_end);

        while(heap_size > 1)
        {
            int index_heap = index_begin + heap_size;

            std::swap(sequence[index_heap], sequence[index_begin]);
            impl::move_down(sequence, index_begin, index_begin, index_heap);
            --heap_size;
        }
    }

    /**
     * Mutowalne sortowanie ciągu przez scalanie top-down.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void mergedown_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        if(index_end == -1)
            index_end = sequence.size();

        impl::validate_indices(sequence.size(), index_begin, index_end);

        if(index_end - index_begin <= 1)
            return;

        int index_middle = (index_begin + index_end) / 2;

        mergedown_sort(sequence, index_begin, index_middle);
        mergedown_sort(sequence, index_middle, index_end);
        impl::merge(sequence, index_begin, index_middle, index_end);
    }

    /**
     * Mutowalne sortowanie ciągu przez scalanie bottom-up.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void mergeup_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        if(index_end == -1)
            index_end = sequence.size();

        impl::validate_indices(sequence.size(), index_begin, index_end);

        if(index_end - index_begin <= 1)
            return;

        for(int i = 2; i < 2 * (index_end - index_begin); i *= 2)
            for(int j = index_begin; j < index_end; j += i)
                impl::merge(sequence, j, std::min(j + i / 2, index_end),
                            std::min(j + i, index_end));
    }

    /**
     * Mutowalne szybkie sortowanie ciągu.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void quick_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        if(index_end == -1)
            index_end = sequence.size();

        impl::validate_indices(sequence.size(), index_begin, index_end);

        if(index_end - index_begin <= 1)
            return;

        int index_pivot = index_begin, index_front = index_begin + 1, index_back = index_end - 1;
        int rdpv = index_begin + impl::choose_pivot(index_end - index_begin);

        std::swap(sequence[index_pivot], sequence[rdpv]);

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

        quick_sort(sequence, index_begin, index_pivot);
        quick_sort(sequence, index_pivot + 1, index_end);
    }
}

#endif
