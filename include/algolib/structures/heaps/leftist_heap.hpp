/*!
 * \file leftist_heap.hpp
 * \brief Structure of leftist heap.
 */
#ifndef LEFTIST_HEAP_HPP_
#define LEFTIST_HEAP_HPP_

#include <cstdlib>
#include <exception>
#include <initializer_list>
#include <memory>
#include <optional>
#include <stdexcept>
#include <vector>

namespace algolib::structures::heaps
{
    template <typename E, typename Compare = std::less<E>>
    class leftist_heap;

    //! \brief Merges two heaps.
    template <typename E, typename Compare>
    leftist_heap<E, Compare> operator+(leftist_heap<E, Compare> heap1,
            const leftist_heap<E, Compare> & heap2);

#pragma region leftist_heap

    template <typename E, typename Compare>
    class leftist_heap
    {
    private:
        class heap_node;

    public:
        using value_compare = Compare;
        using value_type = E;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;

        explicit leftist_heap(const value_compare & compare = value_compare())
            : heap{}, size_{0}, compare{compare}
        {
        }

        template <typename InputIterator>
        leftist_heap(InputIterator first,
                InputIterator last,
                const value_compare & compare = value_compare())
            : leftist_heap(compare)
        {
            for(InputIterator it = first; it != last; ++it)
                this->push(*it);
        }

        leftist_heap(std::initializer_list<value_type> init,
                const value_compare & compare = value_compare())
            : leftist_heap(init.begin(), init.end(), compare)
        {
        }

        ~leftist_heap() = default;
        leftist_heap(const leftist_heap &) = default;
        leftist_heap(leftist_heap &&) = default;
        leftist_heap & operator=(const leftist_heap &) = default;
        leftist_heap & operator=(leftist_heap &&) = default;

        /*!
         * \brief Gets the number of elements in this heap
         * \return the number of elements
         */
        size_type size() const
        {
            return this->size_;
        }

        /*!
         * \brief Check whether this heap is empty
         * \return \c true if the heap is empty, otherwise \c false
         */
        bool empty() const
        {
            return !this->heap;
        }

        //! \brief Removes all elements from this heap.
        void clear()
        {
            this->heap.reset();
            this->size_ = 0;
        }

        /*!
         * \brief Retrieves maximal element from this heap.
         * \return the maximal element
         * \throw std::out_of_range if the heap is empty
         */
        const_reference top() const
        {
            if(this->empty())
                throw std::out_of_range("Heap is empty");

            return this->heap->element;
        }

        /*!
         * \brief Adds new element to this heap.
         * \param element the new element
         */
        void push(const_reference element);

        /*!
         * \brief Adds new element to this heap constructed in-place with given arguments.
         * \param args arguments to forward to the new element's constructor
         */
        template <typename... Args>
        void emplace(Args &&... args);

        //! \brief Removes maximal element from this heap.
        void pop();

        //! \brief Merges given heap to this heap.
        leftist_heap & operator+=(const leftist_heap & other);

        friend leftist_heap<E, Compare> operator+ <E, Compare>(leftist_heap<E, Compare> heap1,
                const leftist_heap<E, Compare> & heap2);

    private:
        typename heap_node::heap_node_ptr heap;
        size_type size_;
        value_compare compare;
    };

    template <typename E, typename Compare>
    void leftist_heap<E, Compare>::push(typename leftist_heap<E, Compare>::const_reference element)
    {
        typename heap_node::heap_node_ptr new_node =
                std::make_shared<const heap_node>(element, this->compare);

        this->heap = this->empty() ? new_node : this->heap->merge(new_node);
        ++this->size_;
    }

    template <typename E, typename Compare>
    template <typename... Args>
    void leftist_heap<E, Compare>::emplace(Args &&... args)
    {
        typename heap_node::heap_node_ptr new_node = std::make_shared<const heap_node>(
                value_type(std::forward<Args>(args)...), this->compare);

        this->heap = this->empty() ? new_node : this->heap->merge(new_node);
        ++this->size_;
    }

    template <typename E, typename Compare>
    void leftist_heap<E, Compare>::pop()
    {
        if(this->empty())
            throw std::out_of_range("Heap is empty");

        this->heap = this->heap->pop();
        --this->size_;
    }

    template <typename E, typename Compare>
    leftist_heap<E, Compare> & leftist_heap<E, Compare>::operator+=(
            const leftist_heap<E, Compare> & other)
    {
        this->heap = this->empty() ? other.heap : this->heap->merge(other.heap);
        this->size_ += other.size_;
        return *this;
    }

#pragma endregion

    template <typename E, typename Compare>
    leftist_heap<E, Compare> operator+(leftist_heap<E, Compare> heap1,
            const leftist_heap<E, Compare> & heap2)
    {
        heap1 += heap2;
        return heap1;
    }

#pragma region heap_node

    template <typename E, typename Compare>
    class leftist_heap<E, Compare>::heap_node
        : public std::enable_shared_from_this<typename leftist_heap<E, Compare>::heap_node>
    {
    public:
        using heap_node_ptr = std::shared_ptr<const heap_node>;

        heap_node(const value_type & element,
                const heap_node_ptr & node1,
                const heap_node_ptr & node2,
                const value_compare & compare)
            : element{element}, compare{compare}
        {
            int rank1 = node1 ? node1->rank : 0;
            int rank2 = node2 ? node2->rank : 0;

            if(rank1 < rank2)
            {
                this->rank = rank1 + 1;
                this->left = node2;
                this->right = node1;
            }
            else
            {
                this->rank = rank2 + 1;
                this->left = node1;
                this->right = node2;
            }
        }

        heap_node(const value_type & element, const value_compare & compare)
            : heap_node(element, nullptr, nullptr, compare)
        {
        }

        ~heap_node() = default;
        heap_node(const heap_node &) = default;
        heap_node(heap_node &&) = default;
        heap_node & operator=(const heap_node &) = default;
        heap_node & operator=(heap_node &&) = default;

        heap_node_ptr pop() const
        {
            return left ? left->merge(right) : right;
        }

        heap_node_ptr merge(const heap_node_ptr & node) const;

    public:
        int rank;
        value_type element;
        heap_node_ptr left;
        heap_node_ptr right;
        value_compare compare;
    };

    template <typename E, typename Compare>
    std::shared_ptr<const typename leftist_heap<E, Compare>::heap_node>
            leftist_heap<E, Compare>::heap_node::merge(const heap_node_ptr & node) const
    {
        return !node ? this->shared_from_this()
               : compare(node->element, this->element)
                       ? std::make_shared<heap_node>(this->element, this->left,
                                 this->right ? this->right->merge(node) : node, this->compare)
                       : std::make_shared<heap_node>(node->element, node->left,
                                 node->right ? node->right->merge(this->shared_from_this())
                                             : this->shared_from_this(),
                                 node->compare);
    }

#pragma endregion
}

#endif
