// ALGORYTMY SORTOWANIA
#include "sorting.hpp"

namespace details = algolib::detail;

template<typename T>
void details::move_down(std::vector<T> & heap, int vertex, int index_begin, int index_end)
{
    int next_vertex = -1, left_vertex = (vertex<<1)-index_begin+1, right_vertex = (vertex<<1)-index_begin+2;

    if(right_vertex <= index_end)
        next_vertex = heap[right_vertex] < heap[left_vertex] ? left_vertex : right_vertex;

    if(left_vertex == index_end)
        next_vertex = left_vertex;

    if(next_vertex >= 0)
    {
        if( heap[next_vertex] > heap[vertex] )
            swap( heap[next_vertex], heap[vertex] );

        move_down(heap, next_vertex, index_begin, index_end);
    }
}

template<typename T>
void details::merge(std::vector<T> & sequence, int index_begin, int index_middle, int index_end)
{
    std::vector<T> ordered;
    int iter1 = index_begin, iter2 = index_middle+1;

     while(iter1 <= index_middle && iter2 <= index_end)
        if( sequence[iter1] < sequence[iter2] )
        {
            ordered.push_back( sequence[iter1] );
            ++iter1;
        }
        else
        {
            ordered.push_back( sequence[iter2] );
            ++iter2;
        }

    if(iter1 <= index_middle)
        for(int i = iter1; i <= index_middle; ++i)
            ordered.push_back( sequence[i] );

    if(iter2 <= index_end)
        for(int i = iter2; i <= index_end; ++i)
            ordered.push_back( sequence[i] );

    for(int i = 0; i < ordered.size(); ++i)
        sequence[index_begin+i] = ordered[i];
}

int details::choose_pivot(int size)
{
    srand( time(0) );

    int candidate1 = rand()%size, candidate2 = rand()%size, candidate3 = rand()%size;

    if( std::min(candidate2, candidate3) <= candidate1
        && candidate1 <= std::max(candidate2, candidate3) )
        return candidate2;
    else if( std::min(candidate1, candidate3) <= candidate2
             && candidate2 <= std::max(candidate1, candidate3) )
        return candidate2;
    else
        return candidate3;
}

void algolib::angle_sort(std::vector<point2D> & points)
{
    auto angle = [](const point2D & pt)
        {
            double ang = atan2(pt.second, pt.first)*90/acos(0);

            return pt.second >= 0.0 ? ang : ang+360.0;
        };

    auto radius = [](const point2D & pt)
        {
           return pt.first*pt.first+pt.second*pt.second;
        };

    auto comparator = [=](const point2D & pt1, const point2D & pt2) -> bool
        {
            double angle1 = angle(pt1), angle2 = angle(pt2);

            return angle1 != angle2 ? angle1 < angle2 : radius(pt1) <= radius(pt2);
        };

    sort(points.begin(), points.end(), comparator);
}

std::vector<point2D> algolib::angle_sorted(std::vector<point2D> points)
{
    angle_sort(points);

    return points;
}

template<typename T>
void algolib::heap_sort(std::vector<T> & sequence, int index_begin, int index_end)
{
    index_begin = (index_begin+sequence.size())%sequence.size();
    index_end = (index_end+sequence.size())%sequence.size();

    int heap_size = index_end-index_begin;

     for(int i = index_begin+heap_size/2; i >= index_begin; --i)
        details::move_down(sequence, i, index_begin, index_end);

    while(heap_size > 1)
    {
        int index_heap = index_begin+heap_size;

        std::swap( sequence[index_heap], sequence[index_begin] );
        details::move_down(sequence, index_begin, index_begin, index_heap-1);
    }
}

template<typename T>
std::vector<int> algolib::heap_sorted(std::vector<T> sequence, int index_begin, int index_end)
{
    heap_sort(sequence, index_begin, index_end);

    return sequence;
}

template<typename T>
void algolib::merge_sort(std::vector<T> & sequence, int index_begin, int index_end)
{
    index_begin = (index_begin+sequence.size())%sequence.size();
    index_end = (index_end+sequence.size())%sequence.size();

     if(index_begin < index_end)
     {
        int index_middle = (index_begin+index_end)/2;

        merge_sort(sequence, index_begin, index_middle);
        merge_sort(sequence, index_middle+1, index_end);
        details::merge(sequence, index_begin, index_middle, index_end);
    }
}

template<typename T>
std::vector<T> algolib::merge_sorted(std::vector<T> sequence, int index_begin, int index_end)
{
    merge_sort(sequence, index_begin, index_end);

    return sequence;
}

template<typename T>
void algolib::quick_sort(std::vector<T> & sequence, int index_begin, int index_end)
{
    index_begin = (index_begin+sequence.size())%sequence.size();
    index_end = (index_end+sequence.size())%sequence.size();

    if(index_begin < index_end)
    {
        int index_pivot = index_begin, index_front = index_begin+1, index_back = index_end;
        int rdpv = index_begin+details::choose_pivot(index_end-index_begin+1);

        std::swap( sequence[index_pivot], sequence[rdpv] );

        while(index_pivot < index_back)
            if( sequence[index_front] < sequence[index_pivot] )
            {
                std::swap( sequence[index_front], sequence[index_pivot] );
                index_pivot = index_front;
                ++index_front;
            }
            else
            {
                swap( sequence[index_front], sequence[index_back] );
                --index_back;
            }

        quick_sort(sequence, index_begin, index_pivot-1);
        quick_sort(sequence, index_pivot+1, index_end);
    }
}

template<typename T>
std::vector<T> algolib::quick_sorted(std::vector<T> sequence, int index_begin, int index_end)
{
    quick_sort(sequence, index_begin, index_end);

    return sequence;
}
