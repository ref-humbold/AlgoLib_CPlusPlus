/*!
 * \file disjoint_sets.hpp
 * \brief Structure of disjoint sets (union-find)
 */
#ifndef DISJOINT_SETS_HPP_
#define DISJOINT_SETS_HPP_

#include <cstdlib>
#include <algorithm>
#include <exception>
#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace algolib::structures
{
    template <typename E>
    class disjoint_sets
    {
    public:
        disjoint_sets() : size_{0}
        {
        }

        explicit disjoint_sets(std::initializer_list<E> universe) : size_{universe.size()}
        {
            for(E e : universe)
                this->represents.emplace(e, e);
        }

        template <typename InputIterator>
        disjoint_sets(InputIterator first, InputIterator last);

        ~disjoint_sets() = default;
        disjoint_sets(const disjoint_sets & ds) = default;
        disjoint_sets(disjoint_sets && ds) noexcept = default;
        disjoint_sets & operator=(const disjoint_sets & ds) = default;
        disjoint_sets & operator=(disjoint_sets && ds) noexcept = default;

        //! \return \code true if the structure is empty, otherwise \code false
        bool empty() const
        {
            return this->size_ == 0;
        }

        //! \return number of sets
        size_t size() const
        {
            return this->size_;
        }

        /*!
         * \brief Checks whether given element in one of the sets in the structure.
         * \param element an element
         * \return \code true if element belongs to the structure, otherwise \code false
         */
        bool contains(const E & element) const
        {
            return this->represents.find(element) != this->represents.end();
        }

        /*!
         * \brief Adds new element to the set represented by another element.
         * \param element a new element
         * \param represent represent of the set
         */
        void insert(const E & element, const E & represent);

        /*!
         * \brief Adds new element as a singleton set.
         * \param element a new element
         */
        void insert(const E & element);

        /*!
         * \brief Adds new elements to the set represented by another element.
         * \param first beginning of elements range
         * \param last end of elements range
         * \param represent represent of the set
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last, const E & represent);

        /*!
         * \brief Adds new elements as singleton sets.
         * \param first beginning of elements range
         * \param last end of elements range
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last);

        /*!
         * \brief Finds represent of the set with given element.
         * \param element an element
         * \return represent of the element
         */
        const E & operator[](const E & element);

        /*!
         * \brief Finds represent of the set with given element.
         * \param element an element
         * \return represent of the element
         */
        const E & operator[](const E & element) const;

        /*!
         * \brief Finds a represent of the element.
         * \param element an element
         * \return optional of represent of the element
         */
        std::optional<E> find_set(const E & element)
        try
        {
            return std::optional<E>(this->operator[](element));
        }
        catch(const std::out_of_range & e)
        {
            return std::nullopt;
        }

        /*!
         * \brief Finds a represent of the element.
         * \param element an element
         * \return optional of represent of the element
         */
        std::optional<E> find_set(const E & element) const
        try
        {
            return std::optional<E>(this->operator[](element));
        }
        catch(const std::out_of_range & e)
        {
            return std::nullopt;
        }

        /*!
         * \brief Performs union of two sets in the structure.
         * \param element1 element from the first set
         * \param element2 element from the second set
         */
        void union_set(const E & element1, const E & element2);

        /*!
         * \brief Tests whether two elements belong to the same set.
         * \param element1 element from the first set
         * \param element2 element from the second set
         * \return \code true if both element are in the same set, otherwise \code false
         */
        bool is_same_set(const E & element1, const E & element2);

        /*!
         * \brief Tests whether two elements belong to the same set.
         * \param element1 element from the first set
         * \param element2 element from the second set
         * \return \code true if both element are in the same set, otherwise \code false
         */
        bool is_same_set(const E & element1, const E & element2) const;

    private:
        std::unordered_map<E, E> represents;
        size_t size_;
    };

    template <typename E>
    template <typename InputIterator>
    disjoint_sets<E>::disjoint_sets(InputIterator first, InputIterator last) : disjoint_sets()
    {
        for(InputIterator it = first; it != last; ++it)
        {
            this->represents.emplace(*it, *it);
            ++this->size_;
        }
    }

    template <typename E>
    void disjoint_sets<E>::insert(const E & element, const E & represent)
    {
        if(this->contains(element))
            throw std::invalid_argument("New value already present");

        if(!this->contains(represent))
            throw std::invalid_argument("Represent value not present");

        this->represents.emplace(element, this->operator[](represent));
    }

    template <typename E>
    void disjoint_sets<E>::insert(const E & element)
    {
        if(this->contains(element))
            throw std::invalid_argument("New value already present");

        this->represents.emplace(element, element);
        this->size_++;
    }

    template <typename E>
    template <typename InputIterator>
    void disjoint_sets<E>::insert(InputIterator first, InputIterator last)
    {
        for(InputIterator it = first; it != last; ++it)
            if(this->contains(*it))
                throw std::invalid_argument("New value already present");

        for(InputIterator it = first; it != last; ++it)
        {
            this->represents.emplace(*it, *it);
            this->size_++;
        }
    }

    template <typename E>
    template <typename InputIterator>
    void disjoint_sets<E>::insert(InputIterator first, InputIterator last, const E & represent)
    {
        for(InputIterator it = first; it != last; ++it)
            if(this->contains(*it))
                throw std::invalid_argument("New value already present");

        for(InputIterator it = first; it != last; ++it)
            this->represents.emplace(*it, this->operator[](represent));
    }

    template <typename E>
    const E & disjoint_sets<E>::operator[](const E & element)
    {
        if(this->represents.at(element) != element)
            this->represents[element] = this->operator[](this->represents[element]);

        return this->represents.at(element);
    }

    template <typename E>
    const E & disjoint_sets<E>::operator[](const E & element) const
    {
        return this->represents.at(element) == element
                       ? element
                       : this->operator[](this->represents.at(element));
    }

    template <typename E>
    void disjoint_sets<E>::union_set(const E & element1, const E & element2)
    {
        if(this->is_same_set(element1, element2))
            return;

        this->represents[this->operator[](element1)] = this->operator[](element2);
        --this->size_;
    }

    template <typename E>
    bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2)
    {
        return this->operator[](element1) == this->operator[](element2);
    }

    template <typename E>
    bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2) const
    {
        return this->operator[](element1) == this->operator[](element2);
    }
}

#endif
