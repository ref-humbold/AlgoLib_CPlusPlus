/*!
 * \file pairing_heap.hpp
 * \brief Structure of pairing heap.
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

namespace algolib::structures::heaps
{
    template <typename E, typename Compare = std::less<E>>
    class pairing_heap;

    //! \brief Merges two heaps.
    template <typename E, typename Compare>
    pairing_heap<E, Compare>
            operator+(pairing_heap<E, Compare> heap1, const pairing_heap<E, Compare> & heap2);

#pragma region pairing_heap

    template <typename E, typename Compare>
    class pairing_heap
    {
    private:
        class heap_node;
        class heap_node_list;

    public:
        using value_compare = Compare;
        using value_type = E;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;

        explicit pairing_heap(const value_compare & compare = value_compare())
            : heap{std::nullopt}, size_{0}, compare{compare}
        {
        }

        template <typename InputIterator>
        pairing_heap(
                InputIterator first,
                InputIterator last,
                const value_compare & compare = value_compare())
            : pairing_heap(compare)
        {
            for(InputIterator it = first; it != last; ++it)
                this->push(*it);
        }

        pairing_heap(
                std::initializer_list<value_type> init,
                const value_compare & compare = value_compare())
            : pairing_heap(init.begin(), init.end(), compare)
        {
        }

        ~pairing_heap() = default;
        pairing_heap(const pairing_heap &) = default;
        pairing_heap(pairing_heap &&) = default;
        pairing_heap & operator=(const pairing_heap &) = default;
        pairing_heap & operator=(pairing_heap &&) = default;

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
        pairing_heap & operator+=(const pairing_heap & other);

        friend pairing_heap<E, Compare> operator+ <E, Compare>(
                pairing_heap<E, Compare> heap1, const pairing_heap<E, Compare> & heap2);

    private:
        std::optional<heap_node> heap;
        size_type size_;
        value_compare compare;
    };

    template <typename E, typename Compare>
    void pairing_heap<E, Compare>::push(typename pairing_heap<E, Compare>::const_reference element)
    {
        if(this->empty())
            this->heap.emplace(element, this->compare);
        else
            this->heap = this->heap->merge(heap_node(element, this->compare));

        ++this->size_;
    }

    template <typename E, typename Compare>
    template <typename... Args>
    void pairing_heap<E, Compare>::emplace(Args &&... args)
    {
        if(this->empty())
            this->heap.emplace(value_type(std::forward<Args>(args)...), this->compare);
        else
            this->heap = this->heap->merge(
                    heap_node(value_type(std::forward<Args>(args)...), this->compare));

        ++this->size_;
    }

    template <typename E, typename Compare>
    void pairing_heap<E, Compare>::pop()
    {
        if(this->empty())
            throw std::out_of_range("Heap is empty");

        this->heap = this->heap->pop();
        --this->size_;
    }

    template <typename E, typename Compare>
    pairing_heap<E, Compare> &
            pairing_heap<E, Compare>::operator+=(const pairing_heap<E, Compare> & other)
    {
        this->heap = this->empty() ? other.heap : this->heap->merge(other.heap);
        this->size_ += other.size_;
        return *this;
    }

#pragma endregion

    template <typename E, typename Compare>
    pairing_heap<E, Compare>
            operator+(pairing_heap<E, Compare> heap1, const pairing_heap<E, Compare> & heap2)
    {
        heap1 += heap2;
        return heap1;
    }

#pragma region heap_node

    template <typename E, typename Compare>
    class pairing_heap<E, Compare>::heap_node
    {
    public:
        heap_node(
                const value_type & element,
                const std::shared_ptr<const heap_node_list> & children,
                const value_compare & compare)
            : element{element}, children{children}, compare{compare}
        {
        }

        heap_node(const value_type & element, const value_compare & compare)
            : heap_node(element, nullptr, compare)
        {
        }

        ~heap_node() = default;
        heap_node(const heap_node &) = default;
        heap_node(heap_node &&) = default;
        heap_node & operator=(const heap_node &) = default;
        heap_node & operator=(heap_node &&) = default;

        heap_node append(const value_type & item) const;

        std::optional<heap_node> pop() const
        {
            return this->merge_pairs(this->children);
        }

        heap_node merge(const std::optional<heap_node> & node) const;

    private:
        std::optional<heap_node>
                merge_pairs(const std::shared_ptr<const heap_node_list> & list) const;

    public:
        value_type element;
        std::shared_ptr<const heap_node_list> children;
        value_compare compare;
    };

    template <typename E, typename Compare>
    typename pairing_heap<E, Compare>::heap_node
            pairing_heap<E, Compare>::heap_node::append(const value_type & item) const
    {
        return compare(item, this->element)
                       ? heap_node(
                               this->element,
                               std::make_shared<const heap_node_list>(
                                       heap_node(item, this->compare), this->children),
                               this->compare)
                       : heap_node(
                               item, std::make_shared<const heap_node_list>(*this), this->compare);
    }

    template <typename E, typename Compare>
    typename pairing_heap<E, Compare>::heap_node
            pairing_heap<E, Compare>::heap_node::merge(const std::optional<heap_node> & node) const
    {
        return !node ? *this
               : compare(node->element, this->element)
                       ? heap_node(
                               this->element,
                               std::make_shared<const heap_node_list>(*node, this->children),
                               this->compare)
                       : heap_node(
                               node->element,
                               std::make_shared<const heap_node_list>(*this, node->children),
                               node->compare);
    }

    template <typename E, typename Compare>
    std::optional<typename pairing_heap<E, Compare>::heap_node>
            pairing_heap<E, Compare>::heap_node::merge_pairs(
                    const std::shared_ptr<const heap_node_list> & list) const
    {
        if(!list)
            return std::nullopt;

        if(!list->next)
            return list->node;

        return list->node.merge(list->next->node).merge(merge_pairs(list->next->next));
    }

#pragma endregion
#pragma region heap_node_list

    template <typename E, typename Compare>
    class pairing_heap<E, Compare>::heap_node_list
    {
    public:
        explicit heap_node_list(
                const heap_node & node,
                const std::shared_ptr<const heap_node_list> & next = nullptr)
            : node{node}, next{next}
        {
        }

        ~heap_node_list() = default;
        heap_node_list(const heap_node_list &) = default;
        heap_node_list(heap_node_list &&) = default;
        heap_node_list & operator=(const heap_node_list &) = default;
        heap_node_list & operator=(heap_node_list &&) = default;

        heap_node node;
        std::shared_ptr<const heap_node_list> next;
    };

#pragma endregion
}

#endif
