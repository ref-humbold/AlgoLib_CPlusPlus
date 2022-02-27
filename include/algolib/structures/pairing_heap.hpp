/*!
 * \file pairing_heap.hpp
 * \brief Structure of pairing heap
 */
#ifndef PAIRING_HEAP_HPP_
#define PAIRING_HEAP_HPP_

#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

namespace algolib::structures
{
#pragma region pairing_heap

    template <typename E, typename Compare = std::less<E>>
    class pairing_heap
    {
    private:
        class heap_node_list;
        class heap_node;

    public:
        using value_compare = Compare;
        using value_type = E;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;

        explicit pairing_heap(const value_compare & compare = value_compare())
            : size_{0}, compare{compare}
        {
        }

        template <typename InputIterator>
        pairing_heap(InputIterator first, InputIterator last,
                     const value_compare & compare = value_compare())
            : pairing_heap(compare)
        {
            for(InputIterator it = first; it != last; ++it)
                this->push(*it);
        }

        ~pairing_heap() = default;
        pairing_heap(const pairing_heap &) = default;
        pairing_heap(pairing_heap &&) = default;
        pairing_heap & operator=(const pairing_heap &) = default;
        pairing_heap & operator=(pairing_heap &&) = default;

        //! \return \c true if this pairing heap is empty, otherwise \c false
        bool empty() const
        {
            return this->size_ == 0;
        }

        //! \return number of elements in this pairing heap
        size_type size() const
        {
            return this->size_;
        }

        //! \brief Removes all elements from this pairing heap.
        void clear()
        {
            this->size_ = 0;
        }

        void push(const_reference element);

        void pop();

    private:
        size_type size_;
        value_compare compare;
    };

    template <typename E, typename Compare>
    void pairing_heap<E, Compare>::push(typename pairing_heap<E, Compare>::const_reference element)
    {
        ++this->size_;
    }

    template <typename E, typename Compare>
    void pairing_heap<E, Compare>::pop()
    {
        if(!empty())
            --this->size_;
    }

#pragma endregion
#pragma region heap_node_list

    template <typename E, typename Compare>
    class pairing_heap<E, Compare>::heap_node_list
    {
    };

#pragma endregion
#pragma region heap_node

    template <typename E, typename Compare>
    class pairing_heap<E, Compare>::heap_node
    {
    };

#pragma endregion
}

#endif
