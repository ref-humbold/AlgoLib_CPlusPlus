// ALGORYTMY SORTOWANIA
#ifndef SORTING_HPP
#define SORTING_HPP

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <algorithm>

using point2D_t = std::pair<double, double>;

namespace detail
{
    /**
    Przywracanie własności kopca.
    @param heap kopiec
    @param vertex wierzchołek kopca
    @param index_begin początkowy indeks kopca
    @param index_end końcowy indeks kopca
    */
    template<typename T>
    void move_down(std::vector<T> & heap, int vertex, int index_begin, int index_end);

    /**
    Scalanie dwóch uporządkowanych fragmentów ciągu.
    @param sequence ciąg
    @param index_begin początek fragmentu
    @param index_middle środek fragmentu
    @param index_end koniec fragmentu
    */
    template<typename T>
    void merge(std::vector<T> & sequence, int index_begin, int index_middle, int index_end);

    /**
    Losowanie piwota.
    @param size liczba elementów
    @return indeks piwota
    */
    int choose_pivot(int size);
}

namespace algolib
{
    /**
    Mutowalne sortowanie kątowe punktów na płaszczyźnie.
    @param points lista punktów
    */
    void angle_sort(std::vector<point2D_t> & points);

    /**
    Niemutowalne sortowanie kątowe punktów na płaszczyźnie.
    @param points lista punktów
    @return lista punktów posortowana względem kąta
    */
    std::vector<point2D_t> angle_sorted(std::vector<point2D_t> points);

    /**
    Mutowalne sortowanie ciągu przez kopcowanie.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    */
    template<typename T>
    void heap_sort(std::vector<T> & sequence, int index_begin=0, int index_end=-1);

    /**
    Niemutowalne sortowanie ciągu przez kopcowanie.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    */
    template<typename T>
    std::vector<int> heap_sorted(std::vector<T> sequence, int index_begin=0, int index_end=-1);

    /**
    Mutowalne sortowanie ciągu przez scalanie.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    */
    template<typename T>
    void merge_sort(std::vector<T> & sequence, int index_begin=0, int index_end=-1);

    /**
    Niemutowalne sortowanie ciągu przez scalanie.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    @return posortowany ciąg
    */
    template<typename T>
    std::vector<T> merge_sorted(std::vector<T> sequence, int index_begin=0, int index_end=-1);

    /**
    Mutowalne szybkie sortowanie ciągu.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    */
    template<typename T>
    void quick_sort(std::vector<T> & sequence, int index_begin=0, int index_end=-1);

    /**
    Niemutowalne szybkie sortowanie ciągu.
    @param sequence ciąg
    @param index_begin początkowy indeks ciągu
    @param index_end końcowy indeks ciągu
    @return posortowany ciąg
    */
    template<typename T>
    std::vector<T> quick_sorted(std::vector<T> sequence, int index_begin=0, int index_end=-1);
}

#endif
