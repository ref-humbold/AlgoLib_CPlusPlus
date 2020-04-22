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
        template <typename E, typename Container = std::vector<E>,
                  typename Compare = std::less<typename Container::value_type>>
        class double_heap
        {
        public:
            using container_type = Container;
            using value_type = E;
            using reference = typename container_type::reference;
            using const_reference = typename container_type::const_reference;
            using size_type = size_t;

            explicit double_heap(const Compare & compare = Compare())
                : heap{Container()}, compare{compare}
            {
            }

            explicit double_heap(std::initializer_list<value_type> il,
                                 const Compare & compare = Compare())
                : heap{Container()}, compare{compare}
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
            const_reference min() const
            {
                if(heap.empty())
                    throw std::out_of_range("Double heap is empty");

                return *(heap.begin() + INDEX_MIN);
            }

            /*!
             * \brief Retrieves maximal element from this double heap.
             * \return maximal element
             */
            const_reference max() const
            {
                return heap.size() <= 1 ? min() : *(heap.begin() + INDEX_MAX);
            }

            /*!
             * \brief Adds a new value to this double heap.
             * \param element value to be added
             */
            void push(const_reference element);

            //! \brief Removes minimal element from this double heap.
            void pop_min();

            //! \brief Removes maximal element from this double heap.
            void pop_max();

            //! \brief Removes all elements in this double heap.
            void clear()
            {
                heap = Container();
            }

        private:
            void move_to_min(size_type index);
            void move_to_max(size_type index);
            void step_to_min(size_type index, size_type next_index);
            void step_to_max(size_type index, size_type next_index);

            static const size_type INDEX_MIN = 0;
            static const size_type INDEX_MAX = 1;

            container_type heap;  // Heap respresentation
            Compare compare;  // Comparator
        };

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::push(const_reference element)
        {
            heap.push_back(element);

            if(heap.size() > 1)
            {
                size_type index = heap.size() - 1;

                if(index % 2 == 1)
                {
                    if(compare(heap[index], heap[index - 1]))
                    {
                        std::swap(heap[index], heap[index - 1]);
                        move_to_min(index - 1);
                    }
                    else
                        move_to_max(index);
                }
                else
                {
                    size_type new_index = ((index + 1) / 2 - 1) / 2 * 2 + 1;

                    if(compare(heap[new_index], heap[index]))
                    {
                        std::swap(heap[index], heap[new_index]);
                        move_to_max(new_index);
                    }
                    else
                        move_to_min(index);
                }
            }
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::pop_min()
        {
            if(heap.empty())
                throw std::out_of_range("Double heap is empty");

            heap[INDEX_MIN] = heap.back();
            heap.pop_back();
            move_to_max(INDEX_MIN);
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::pop_max()
        {
            if(heap.size() <= 1)
                return pop_min();

            heap[INDEX_MAX] = heap.back();
            heap.pop_back();
            move_to_min(INDEX_MAX);
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::move_to_min(size_type index)
        {
            if(index == INDEX_MIN)
                return;

            if(index % 2 == 0)
                step_to_min(index, (index / 2 - 1) / 2 * 2);
            else
            {
                size_type left_index = index + index + 1;
                size_type right_index = index + index + 3;

                if(right_index < heap.size())
                {
                    size_type child_index =
                            compare(heap[right_index], heap[left_index]) ? left_index : right_index;

                    step_to_min(index, child_index);
                }
                else if(left_index < heap.size())
                    step_to_min(index, left_index);
                else if(index < heap.size())
                    step_to_min(index, index - 1);
            }
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::move_to_max(size_type index)
        {
            if(index == INDEX_MAX)
                return;

            if(index % 2 == 1)
                step_to_max(index, (index / 2 - 1) / 2 * 2 + 1);
            else
            {
                size_type left_index = index + index + 2;
                size_type right_index = index + index + 4;

                if(right_index < heap.size())
                {
                    size_type child_index =
                            compare(heap[left_index], heap[right_index]) ? left_index : right_index;

                    step_to_max(index, child_index);
                }
                else if(left_index < heap.size())
                    step_to_max(index, left_index);
                else if(index + 1 < heap.size())
                    step_to_max(index, index + 1);
            }
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::step_to_min(size_type index, size_type next_index)
        {
            if(compare(heap[index], heap[next_index]))
            {
                std::swap(heap[index], heap[next_index]);
                move_to_min(next_index);
            }
        }

        template <typename E, typename Container, typename Compare>
        void double_heap<E, Container, Compare>::step_to_max(size_type index, size_type next_index)
        {
            if(compare(heap[next_index], heap[index]))
            {
                std::swap(heap[index], heap[next_index]);
                move_to_max(next_index);
            }
        }
    }
}

#endif
