/*!
 * \file avl_tree.hpp
 * \brief Structure of double heap
 */
#ifndef DOUBLE_HEAP_HPP_
#define DOUBLE_HEAP_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <initializer_list>
#include <vector>

namespace algolib
{
    namespace structures
    {
        template <typename E, typename Compare = std::less<E>>
        class double_heap
        {
        public:
            using value_type = E;
            using reference = value_type &;
            using const_reference = const value_type &;

            using size_type = size_t;

            explicit double_heap(const Compare & cmp = Compare()) : cmp{cmp}
            {
            }

            explicit double_heap(std::initializer_list<value_type> il,
                                 const Compare & cmp = Compare())
                : cmp{cmp}
            {
                for(const auto & e : il)
                    push(e);
            }

            ~double_heap() = default;
            double_heap(const double_heap &) = default;
            double_heap(double_heap &&) = default;
            double_heap & operator=(const double_heap &) = default;
            double_heap & operator=(double_heap &&) = default;

            size_type size() const
            {
                return heap.size();
            }

            bool empty() const
            {
                return heap.empty();
            }

            const_reference front() const
            {
                if(heap.size() == 0)
                    throw std::out_of_range();

                return heap[0];
            }

            const_reference back() const
            {
                return heap.size() <= 1 ? front() : heap[1];
            }

            void push(const_reference element);
            void pop_front();
            void pop_back();

        private:
            std::vector<E> heap;  // Heap respresentation
            Compare cmp;  // Comparator
        };

        template <typename E, typename Compare>
        void double_heap<E, Compare>::push(const_reference element)
        {
            // TODO
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::pop_front()
        {
            // TODO
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::pop_back()
        {
            // TODO
        }
    }
}

#endif
