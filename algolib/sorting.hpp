// ALGORYTMY SORTOWANIA
#ifndef SORTING_HPP
#define SORTING_HPP

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>

using point2D_t = std::pair<double, double>;

namespace detail
{
    /**
     * Przywracanie własności kopca.
     * @param heap kopiec
     * @param vertex wierzchołek kopca
     * @param index_begin początkowy indeks kopca
     * @param index_end końcowy indeks kopca
     */
    template <typename T>
    void move_down(std::vector<T> & heap, int vertex, int index_begin, int index_end)
    {
        int next_vertex = -1;
        int left_vertex = (vertex * 2) - index_begin + 1;
        int right_vertex = (vertex * 2) - index_begin + 2;

        if(right_vertex <= index_end)
            next_vertex = heap[right_vertex] < heap[left_vertex] ? left_vertex : right_vertex;

        if(left_vertex == index_end)
            next_vertex = left_vertex;

        if(next_vertex < 0)
            return;

        if(heap[next_vertex] > heap[vertex])
            swap(heap[next_vertex], heap[vertex]);

        move_down(heap, next_vertex, index_begin, index_end);
    }

    /**
     * Scalanie dwóch uporządkowanych fragmentów ciągu.
     * @param sequence ciąg
     * @param index_begin początek fragmentu
     * @param index_middle środek fragmentu
     * @param index_end koniec fragmentu
     */
    template <typename T>
    void merge(std::vector<T> & sequence, int index_begin, int index_middle, int index_end)
    {
        std::vector<T> ordered;
        int iter1 = index_begin, iter2 = index_middle + 1;

        while(iter1 <= index_middle && iter2 <= index_end)
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

        if(iter1 <= index_middle)
            for(int i = iter1; i <= index_middle; ++i)
                ordered.push_back(sequence[i]);

        if(iter2 <= index_end)
            for(int i = iter2; i <= index_end; ++i)
                ordered.push_back(sequence[i]);

        for(int i = 0; i < ordered.size(); ++i)
            sequence[index_begin + i] = ordered[i];
    }

    /**
     * Losowanie piwota.
     * @param size liczba elementów
     * @return indeks piwota
     */
    int choose_pivot(int size)
    {
        srand(time(0));

        int candidate1 = rand() % size, candidate2 = rand() % size, candidate3 = rand() % size;

        if(std::min(candidate2, candidate3) <= candidate1
           && candidate1 <= std::max(candidate2, candidate3))
            return candidate2;
        else if(std::min(candidate1, candidate3) <= candidate2
                && candidate2 <= std::max(candidate1, candidate3))
            return candidate2;
        else
            return candidate3;
    }
}

namespace algolib
{
    /**
     * Mutowalne sortowanie kątowe punktów na płaszczyźnie.
     * @param points lista punktów
     */
    void angle_sort(std::vector<point2D_t> & points)
    {
        auto angle = [](const point2D_t & pt) {
            double ang = atan2(pt.second, pt.first) * 180.0 / M_PI;

            return pt.second >= 0.0 ? ang : ang + 360.0;
        };

        auto radius = [](const point2D_t & pt) {
            return pt.first * pt.first + pt.second * pt.second;
        };

        auto comparator = [&](const point2D_t & pt1, const point2D_t & pt2) -> bool {
            double angle1 = angle(pt1), angle2 = angle(pt2);

            return angle1 != angle2 ? angle1 < angle2 : radius(pt1) <= radius(pt2);
        };

        std::sort(points.begin(), points.end(), comparator);
    }

    /**
     * Niemutowalne sortowanie kątowe punktów na płaszczyźnie.
     * @param points lista punktów
     * @return lista punktów posortowana względem kąta
     */
    std::vector<point2D_t> angle_sorted(std::vector<point2D_t> points)
    {
        angle_sort(points);

        return points;
    }

    /**
     * Mutowalne sortowanie ciągu przez kopcowanie.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void heap_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        index_begin = (index_begin + sequence.size()) % sequence.size();
        index_end = (index_end + sequence.size()) % sequence.size();

        int heap_size = index_end - index_begin;

        for(int i = index_begin + heap_size / 2; i >= index_begin; --i)
            detail::move_down(sequence, i, index_begin, index_end);

        while(heap_size > 1)
        {
            int index_heap = index_begin + heap_size;

            std::swap(sequence[index_heap], sequence[index_begin]);
            detail::move_down(sequence, index_begin, index_begin, index_heap - 1);
        }
    }

    /**
     * Niemutowalne sortowanie ciągu przez kopcowanie.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    std::vector<T> heap_sorted(std::vector<T> sequence, int index_begin = 0, int index_end = -1)
    {
        heap_sort(sequence, index_begin, index_end);

        return sequence;
    }

    /**
     * Mutowalne sortowanie ciągu przez scalanie.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     */
    template <typename T>
    void merge_sort(std::vector<T> & sequence, int index_begin = 0, int index_end = -1)
    {
        index_begin = (index_begin + sequence.size()) % sequence.size();
        index_end = (index_end + sequence.size()) % sequence.size();

        if(index_begin >= index_end)
            return;

        int index_middle = (index_begin + index_end) / 2;

        merge_sort(sequence, index_begin, index_middle);
        merge_sort(sequence, index_middle + 1, index_end);
        detail::merge(sequence, index_begin, index_middle, index_end);
    }

    /**
     * Niemutowalne sortowanie ciągu przez scalanie.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     * @return posortowany ciąg
     */
    template <typename T>
    std::vector<T> merge_sorted(std::vector<T> sequence, int index_begin = 0, int index_end = -1)
    {
        merge_sort(sequence, index_begin, index_end);

        return sequence;
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
        index_begin = (index_begin + sequence.size()) % sequence.size();
        index_end = (index_end + sequence.size()) % sequence.size();

        if(index_begin >= index_end)
            return;

        int index_pivot = index_begin, index_front = index_begin + 1, index_back = index_end;
        int rdpv = index_begin + detail::choose_pivot(index_end - index_begin + 1);

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

        quick_sort(sequence, index_begin, index_pivot - 1);
        quick_sort(sequence, index_pivot + 1, index_end);
    }

    /**
     * Niemutowalne szybkie sortowanie ciągu.
     * @param sequence ciąg
     * @param index_begin początkowy indeks ciągu
     * @param index_end końcowy indeks ciągu
     * @return posortowany ciąg
     */
    template <typename T>
    std::vector<T> quick_sorted(std::vector<T> sequence, int index_begin = 0, int index_end = -1)
    {
        quick_sort(sequence, index_begin, index_end);

        return sequence;
    }
}

#endif
