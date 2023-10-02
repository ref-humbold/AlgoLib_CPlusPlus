/*!
 * \file disjoint_sets.hpp
 * \brief Structure of disjoint sets (union-find).
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
    template <typename E, typename Hash = std::hash<E>, typename Equal = std::equal_to<E>>
    class disjoint_sets
    {
    public:
        using hasher = Hash;
        using value_equal = Equal;
        using value_type = E;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;

        disjoint_sets() : size_{0}
        {
        }

        template <typename InputIterator>
        disjoint_sets(InputIterator first, InputIterator last) : disjoint_sets()
        {
            for(InputIterator it = first; it != last; ++it)
            {
                this->represents.emplace(*it, *it);
                ++this->size_;
            }
        }

        disjoint_sets(std::initializer_list<value_type> init)
            : disjoint_sets(init.begin(), init.end())
        {
        }

        ~disjoint_sets() = default;
        disjoint_sets(const disjoint_sets & ds) = default;
        disjoint_sets(disjoint_sets && ds) noexcept = default;
        disjoint_sets & operator=(const disjoint_sets & ds) = default;
        disjoint_sets & operator=(disjoint_sets && ds) noexcept = default;

        //! \return the number of sets
        size_type size() const
        {
            return this->size_;
        }

        //! \return \c true if this structure is empty, otherwise \c false
        bool empty() const
        {
            return this->size_ == 0;
        }

        /*!
         * \brief Checks whether given element belongs to any set.
         * \param element the element
         * \return \c true if element belongs to the structure, otherwise \c false
         */
        bool contains(const_reference element) const
        {
            return this->represents.find(element) != this->represents.end();
        }

        /*!
         * \brief Adds new element as singleton set.
         * \param element the new element
         * \throw std::invalid_argument if the element is already present
         */
        void insert(const_reference element);

        /*!
         * \brief Adds new element to the set represented by another element.
         * \param element the new element
         * \param represent the represent of the set
         * \throw std::invalid_argument if the element is already present
         * \throw std::out_of_range if represent is not present
         */
        void insert(const_reference element, const_reference represent);

        /*!
         * \brief Adds new elements as singleton sets.
         * \param first the beginning of new elements range
         * \param last the end of new elements range
         * \throw std::invalid_argument if any of the elements is already present
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last);

        /*!
         * \brief Adds new elements to the set represented by another element.
         * \param first beginning of new elements range
         * \param last end of new elements range
         * \param represent the represent of the set
         * \throw std::invalid_argument if any of the elements is already present
         * \throw std::out_of_range if represent is not present
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last, const_reference represent);

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element
         * \throw std::out_of_range if element not present
         */
        const_reference operator[](const_reference element);

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element
         * \throw std::out_of_range if element not present
         */
        const_reference operator[](const_reference element) const;

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element, or \c std::nullopt if not found
         */
        std::optional<value_type> find_set(const_reference element)
        try
        {
            return std::make_optional(this->operator[](element));
        }
        catch(const std::out_of_range & e)
        {
            return std::nullopt;
        }

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element, or \c std::nullopt if not found
         */
        std::optional<value_type> find_set(const_reference element) const
        try
        {
            return std::make_optional(this->operator[](element));
        }
        catch(const std::out_of_range & e)
        {
            return std::nullopt;
        }

        /*!
         * \brief Joins two sets together.
         * \param element1 the element from the first set
         * \param element2 the element from the second set
         * \throw std::out_of_range if element not present
         */
        void union_set(const_reference element1, const_reference element2);

        /*!
         * \brief Checks whether given elements belong to the same set.
         * \param element1 the element from the first set
         * \param element2 the element from the second set
         * \return \c true if both element are in the same set, otherwise \c false
         * \throw std::out_of_range if element not present
         */
        bool is_same_set(const_reference element1, const_reference element2);

        /*!
         * \brief Checks whether given elements belong to the same set.
         * \param element1 element from the first set
         * \param element2 element from the second set
         * \return \c true if both element are in the same set, otherwise \c false
         * \throw std::out_of_range if element not present
         */
        bool is_same_set(const_reference element1, const_reference element2) const;

    private:
        std::unordered_map<value_type, value_type, hasher, value_equal> represents;
        size_type size_;
    };

    template <typename E, typename Hash, typename Equal>
    void disjoint_sets<E, Hash, Equal>::insert(
            typename disjoint_sets<E, Hash, Equal>::const_reference element,
            typename disjoint_sets<E, Hash, Equal>::const_reference represent)
    {
        if(this->contains(element))
            throw std::invalid_argument("New value already present");

        if(!this->contains(represent))
            throw std::out_of_range("Represent value not present");

        this->represents.emplace(element, this->operator[](represent));
    }

    template <typename E, typename Hash, typename Equal>
    void disjoint_sets<E, Hash, Equal>::insert(
            typename disjoint_sets<E, Hash, Equal>::const_reference element)
    {
        if(this->contains(element))
            throw std::invalid_argument("New value already present");

        this->represents.emplace(element, element);
        ++this->size_;
    }

    template <typename E, typename Hash, typename Equal>
    template <typename InputIterator>
    void disjoint_sets<E, Hash, Equal>::insert(InputIterator first, InputIterator last)
    {
        for(InputIterator it = first; it != last; ++it)
            if(this->contains(*it))
                throw std::invalid_argument("New value already present");

        for(InputIterator it = first; it != last; ++it)
        {
            this->represents.emplace(*it, *it);
            ++this->size_;
        }
    }

    template <typename E, typename Hash, typename Equal>
    template <typename InputIterator>
    void disjoint_sets<E, Hash, Equal>::insert(
            InputIterator first,
            InputIterator last,
            typename disjoint_sets<E, Hash, Equal>::const_reference represent)
    {
        for(InputIterator it = first; it != last; ++it)
            if(this->contains(*it))
                throw std::invalid_argument("New value already present");

        if(!this->contains(represent))
            throw std::out_of_range("Represent value not present");

        for(InputIterator it = first; it != last; ++it)
            this->represents.emplace(*it, this->operator[](represent));
    }

    template <typename E, typename Hash, typename Equal>
    typename disjoint_sets<E, Hash, Equal>::const_reference
            disjoint_sets<E, Hash, Equal>::operator[](
                    typename disjoint_sets<E, Hash, Equal>::const_reference element)
    {
        if(this->represents.at(element) != element)
            this->represents.at(element) = this->operator[](this->represents.at(element));

        return this->represents.at(element);
    }

    template <typename E, typename Hash, typename Equal>
    typename disjoint_sets<E, Hash, Equal>::const_reference
            disjoint_sets<E, Hash, Equal>::operator[](
                    typename disjoint_sets<E, Hash, Equal>::const_reference element) const
    {
        return this->represents.at(element) == element
                       ? element
                       : this->operator[](this->represents.at(element));
    }

    template <typename E, typename Hash, typename Equal>
    void disjoint_sets<E, Hash, Equal>::union_set(
            typename disjoint_sets<E, Hash, Equal>::const_reference element1,
            typename disjoint_sets<E, Hash, Equal>::const_reference element2)
    {
        if(this->is_same_set(element1, element2))
            return;

        this->represents.at(this->operator[](element1)) = this->operator[](element2);
        --this->size_;
    }

    template <typename E, typename Hash, typename Equal>
    bool disjoint_sets<E, Hash, Equal>::is_same_set(
            typename disjoint_sets<E, Hash, Equal>::const_reference element1,
            typename disjoint_sets<E, Hash, Equal>::const_reference element2)
    {
        return this->operator[](element1) == this->operator[](element2);
    }

    template <typename E, typename Hash, typename Equal>
    bool disjoint_sets<E, Hash, Equal>::is_same_set(
            typename disjoint_sets<E, Hash, Equal>::const_reference element1,
            typename disjoint_sets<E, Hash, Equal>::const_reference element2) const
    {
        return this->operator[](element1) == this->operator[](element2);
    }
}

#endif
