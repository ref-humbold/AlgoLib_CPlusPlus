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
        else if(this->compare(this->heap->element, element))
            this->heap = std::make_optional<heap_node>(
                    element,
                    std::vector<std::shared_ptr<const heap_node>>(
                            {std::make_shared<const heap_node>(*this->heap)}),
                    this->compare);
        else
        {
            std::vector<std::shared_ptr<const heap_node>> new_children = {
                    std::make_shared<const heap_node>(element, this->compare),
            };

            std::copy(
                    std::begin(this->heap->children), std::end(this->heap->children),
                    std::back_inserter(new_children));
            this->heap =
                    std::make_optional<heap_node>(this->heap->element, new_children, this->compare);
        }

        ++this->size_;
    }

    template <typename E, typename Compare>
    template <typename... Args>
    void pairing_heap<E, Compare>::emplace(Args &&... args)
    {
        value_type element(std::forward<Args>(args)...);

        this->push(element);
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
        this->heap = this->empty() ? other.heap : std::make_optional(this->heap->merge(other.heap));
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
    private:
        using child_type = std::shared_ptr<const heap_node>;

    public:
        heap_node(
                const value_type & element,
                const std::vector<child_type> & children,
                const value_compare & compare)
            : element{element}, children{children}, compare{compare}
        {
        }

        heap_node(const value_type & element, const value_compare & compare)
            : element{element}, children{std::vector<child_type>()}, compare{compare}
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
            return this->merge_pairs(0);
        }

        heap_node merge(const std::optional<heap_node> & node) const;

    private:
        std::optional<heap_node> merge_pairs(size_t index) const;

    public:
        value_type element;
        std::vector<child_type> children;
        value_compare compare;
    };

    template <typename E, typename Compare>
    typename pairing_heap<E, Compare>::heap_node pairing_heap<E, Compare>::heap_node::append(
            const typename pairing_heap<E, Compare>::value_type & item) const
    {
        if(compare(item, this->element))
        {
            std::vector<child_type> new_children = {
                    std::make_shared<const heap_node>(item, this->compare)};

            std::copy(
                    this->children.begin(), this->children.end(), std::back_inserter(new_children));
            return heap_node(this->element, new_children, this->compare);
        }

        return heap_node(
                item, children_type({std::make_shared<const heap_node>(*this)}), this->compare);
    }

    template <typename E, typename Compare>
    typename pairing_heap<E, Compare>::heap_node pairing_heap<E, Compare>::heap_node::merge(
            const std::optional<pairing_heap<E, Compare>::heap_node> & node) const
    {
        if(!node)
            return *this;

        if(compare(node->element, this->element))
        {
            std::vector<child_type> new_children = {std::make_shared<const heap_node>(*node)};

            std::copy(
                    this->children.begin(), this->children.end(), std::back_inserter(new_children));
            return heap_node(this->element, new_children, this->compare);
        }

        std::vector<child_type> new_children = {std::make_shared<const heap_node>(*this)};

        std::copy(node->children.begin(), node->children.end(), std::back_inserter(new_children));
        return heap_node(node->element, new_children, node->compare);
    }

    template <typename E, typename Compare>
    std::optional<typename pairing_heap<E, Compare>::heap_node>
            pairing_heap<E, Compare>::heap_node::merge_pairs(size_t index) const
    {
        if(index >= this->children.size())
            return std::nullopt;

        if(index == this->children.size() - 1)
            return std::make_optional(*this->children[index]);

        return std::make_optional(this->children[index]
                                          ->merge(std::make_optional(*this->children[index + 1]))
                                          .merge(merge_pairs(index + 2)));
    }

#pragma endregion
}

#endif
