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

            /*!
             * \brief Retrieves minimal element from this double heap.
             * \return minimal element
             */
            const_reference front() const
            {
                if(heap.empty())
                    throw std::out_of_range("Double heap is empty");

                return heap[INDEX_FRONT];
            }

            /*!
             * \brief Retrieves maximal element from this double heap.
             * \return maximal element
             */
            const_reference back() const
            {
                return heap.size() <= 1 ? front() : heap[INDEX_BACK];
            }

            /*!
             * \brief Adds a new value to this double heap.
             * \param element value to be added
             */
            void push(const_reference element);

            //! \brief Removes minimal element from this double heap.
            void pop_front();

            //! \brief Removes maximal element from this double heap.
            void pop_back();

            //! \brief Removes all elements in the tree.
            void clear()
            {
                heap.clear();
            }

        private:
            void move_to_front(size_type index);
            void move_to_back(size_type index);
            void step_to_front(size_type index, size_type next_index);
            void step_to_back(size_type index, size_type next_index);

            static const size_type INDEX_FRONT = 0;
            static const size_type INDEX_BACK = 1;

            std::vector<E> heap;  // Heap respresentation
            Compare cmp;  // Comparator
        };

        template <typename E, typename Compare>
        void double_heap<E, Compare>::push(const_reference element)
        {
            heap.push_back(element);

            if(heap.size() > 1)
            {
                size_type index = heap.size() - 1;

                if(index % 2 == 1)
                {
                    if(cmp(heap[index], heap[index - 1]))
                    {
                        std::swap(heap[index], heap[index - 1]);
                        move_to_front(index - 1);
                    }
                    else
                        move_to_back(index);
                }
                else
                {
                    size_type new_index = ((index + 1) / 2 - 1) / 2 * 2 + 1;

                    if(cmp(heap[new_index], heap[index]))
                    {
                        std::swap(heap[index], heap[new_index]);
                        move_to_back(new_index);
                    }
                    else
                        move_to_front(index);
                }
            }
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::pop_front()
        {
            if(heap.empty())
                throw std::out_of_range("Double heap is empty");

            heap[INDEX_FRONT] = heap.back();
            heap.pop_back();
            move_to_back(INDEX_FRONT);
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::pop_back()
        {
            if(heap.size() <= 1)
                return pop_front();

            heap[INDEX_BACK] = heap.back();
            heap.pop_back();
            move_to_front(INDEX_BACK);
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::move_to_front(size_type index)
        {
            if(index == INDEX_FRONT)
                return;

            if(index % 2 == 0)
                step_to_front(index, (index / 2 - 1) / 2 * 2);
            else
            {
                size_type left_index = index + index + 1;
                size_type right_index = index + index + 3;

                if(right_index < heap.size())
                {
                    size_type child_index =
                            cmp(heap[right_index], heap[left_index]) ? left_index : right_index;

                    step_to_front(index, child_index);
                }
                else if(left_index < heap.size())
                    step_to_front(index, left_index);
                else if(index < heap.size())
                    step_to_front(index, index - 1);
            }
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::move_to_back(size_type index)
        {
            if(index == INDEX_BACK)
                return;

            if(index % 2 == 1)
                step_to_back(index, (index / 2 - 1) / 2 * 2 + 1);
            else
            {
                size_type left_index = index + index + 2;
                size_type right_index = index + index + 4;

                if(right_index < heap.size())
                {
                    size_type child_index =
                            cmp(heap[left_index], heap[right_index]) ? left_index : right_index;

                    step_to_back(index, child_index);
                }
                else if(left_index < heap.size())
                    step_to_back(index, left_index);
                else if(index + 1 < heap.size())
                    step_to_back(index, index + 1);
            }
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::step_to_front(size_type index, size_type next_index)
        {
            if(cmp(heap[index], heap[next_index]))
            {
                std::swap(heap[index], heap[next_index]);
                move_to_front(next_index);
            }
        }

        template <typename E, typename Compare>
        void double_heap<E, Compare>::step_to_back(size_type index, size_type next_index)
        {
            if(cmp(heap[next_index], heap[index]))
            {
                std::swap(heap[index], heap[next_index]);
                move_to_back(next_index);
            }
        }
    }
}

#endif
