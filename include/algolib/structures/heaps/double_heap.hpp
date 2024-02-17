/*!
 * \file double_heap.hpp
 * \brief Structure of double heap.
 */
#ifndef DOUBLE_HEAP_HPP_
#define DOUBLE_HEAP_HPP_

#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <stdexcept>
#include <vector>

namespace algolib::structures::heaps
{
    template <
            typename E,
            typename Container = std::vector<E>,
            typename Compare = std::less<typename Container::value_type>>
    class double_heap
    {
    public:
        using container_type = Container;
        using value_compare = Compare;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;
        using size_type = typename container_type::size_type;

        explicit double_heap(
                const value_compare & compare = value_compare(),
                const container_type & container = container_type())
            : heap{container_type()}, compare{compare}
        {
            for(auto && element : container)
                this->push(element);
        }

        template <typename InputIterator>
        double_heap(
                InputIterator first,
                InputIterator last,
                const value_compare & compare = value_compare())
            : double_heap(compare)
        {
            for(InputIterator it = first; it != last; ++it)
                this->push(*it);
        }

        double_heap(
                std::initializer_list<value_type> init,
                const value_compare & compare = value_compare())
            : double_heap(init.begin(), init.end(), compare)
        {
        }

        ~double_heap() = default;
        double_heap(const double_heap &) = default;
        double_heap(double_heap &&) = default;
        double_heap & operator=(const double_heap &) = default;
        double_heap & operator=(double_heap &&) = default;

        /*!
         * \brief Gets the number of elements in this heap.
         * \return the number of elements
         */
        size_type size() const
        {
            return this->heap.size();
        }

        /*!
         * \brief Checks whether this heap is empty.
         * \return \c true if the heap is empty, otherwise \c false
         */
        bool empty() const
        {
            return this->heap.empty();
        }

        //! \brief Removes all elements from this heap.
        void clear()
        {
            this->heap = container_type();
        }

        /*!
         * \brief Retrieves minimal element from this heap.
         * \return the minimal element
         * \throw std::out_of_range if the heap is empty
         */
        const_reference min() const
        {
            if(this->empty())
                throw std::out_of_range("Heap is empty");

            return *(this->heap.begin() + index_max);
        }

        /*!
         * \brief Retrieves maximal element from this heap.
         * \return the maximal element
         * \throw std::out_of_range if the heap is empty
         */
        const_reference max() const
        {
            return this->heap.size() <= 1 ? this->min() : *(this->heap.begin() + index_min);
        }

        /*!
         * \brief Adds new element to this heap.
         * \param element the new element
         */
        void push(const_reference element);

        /*!
         * \brief Adds new value to this heap constructed in-place with given arguments.
         * \param args the arguments to forward to the new element's constructor
         */
        template <typename... Args>
        void emplace(Args &&... args);

        //! \brief Removes minimal element from this heap.
        void pop_min();

        //! \brief Removes maximal element from this heap.
        void pop_max();

    private:
        void push_heap();
        void move_to_min(size_type index);
        void move_to_max(size_type index);
        void step_to_min(size_type index, size_type next_index);
        void step_to_max(size_type index, size_type next_index);

        static constexpr size_type index_max = 0;
        static constexpr size_type index_min = 1;

        container_type heap;
        value_compare compare;
    };

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::push(const_reference element)
    {
        this->heap.push_back(element);
        this->push_heap();
    }

    template <typename E, typename Container, typename Compare>
    template <typename... Args>
    void double_heap<E, Container, Compare>::emplace(Args &&... args)
    {
        this->heap.emplace_back(std::forward<Args>(args)...);
        this->push_heap();
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::pop_min()
    {
        if(this->empty())
            throw std::out_of_range("Heap is empty");

        *(this->heap.begin() + index_max) = this->heap.back();
        this->heap.pop_back();
        this->move_to_max(index_max);
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::pop_max()
    {
        if(this->heap.size() <= 1)
            return this->pop_min();

        *(this->heap.begin() + index_min) = this->heap.back();
        this->heap.pop_back();
        this->move_to_min(index_min);
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::push_heap()
    {
        if(this->heap.size() > 1)
        {
            size_type index = this->heap.size() - 1;

            if(index % 2 == 1)
            {
                if(compare(*(this->heap.begin() + index), *(this->heap.begin() + index - 1)))
                {
                    std::swap(*(this->heap.begin() + index), *(this->heap.begin() + index - 1));
                    this->move_to_min(index - 1);
                }
                else
                    this->move_to_max(index);
            }
            else
            {
                size_type new_index = ((index + 1) / 2 - 1) / 2 * 2 + 1;

                if(this->compare(*(this->heap.begin() + new_index), *(this->heap.begin() + index)))
                {
                    std::swap(*(this->heap.begin() + index), *(this->heap.begin() + new_index));
                    this->move_to_max(new_index);
                }
                else
                    this->move_to_min(index);
            }
        }
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::move_to_min(size_type index)
    {
        if(index == index_max)
            return;

        if(index % 2 == 0)
            this->step_to_min(index, (index / 2 - 1) / 2 * 2);
        else
        {
            size_type left_index = index + index + 1;
            size_type right_index = index + index + 3;

            if(right_index < this->heap.size())
            {
                size_type child_index = this->compare(
                                                *(this->heap.begin() + right_index),
                                                *(this->heap.begin() + left_index))
                                                ? left_index
                                                : right_index;

                this->step_to_min(index, child_index);
            }
            else if(left_index < this->heap.size())
                this->step_to_min(index, left_index);
            else if(index < this->heap.size())
                this->step_to_min(index, index - 1);
        }
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::move_to_max(size_type index)
    {
        if(index == index_min)
            return;

        if(index % 2 == 1)
            this->step_to_max(index, (index / 2 - 1) / 2 * 2 + 1);
        else
        {
            size_type left_index = index + index + 2;
            size_type right_index = index + index + 4;

            if(right_index < this->heap.size())
            {
                size_type child_index = this->compare(
                                                *(this->heap.begin() + left_index),
                                                *(this->heap.begin() + right_index))
                                                ? left_index
                                                : right_index;

                this->step_to_max(index, child_index);
            }
            else if(left_index < this->heap.size())
                this->step_to_max(index, left_index);
            else if(index + 1 < this->heap.size())
                this->step_to_max(index, index + 1);
        }
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::step_to_min(size_type index, size_type next_index)
    {
        if(this->compare(*(this->heap.begin() + index), *(this->heap.begin() + next_index)))
        {
            std::swap(*(this->heap.begin() + index), *(this->heap.begin() + next_index));
            this->move_to_min(next_index);
        }
    }

    template <typename E, typename Container, typename Compare>
    void double_heap<E, Container, Compare>::step_to_max(size_type index, size_type next_index)
    {
        if(this->compare(*(this->heap.begin() + next_index), *(this->heap.begin() + index)))
        {
            std::swap(*(this->heap.begin() + index), *(this->heap.begin() + next_index));
            this->move_to_max(next_index);
        }
    }
}

#endif
