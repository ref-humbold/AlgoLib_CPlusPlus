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
#include <unordered_set>
#include <vector>

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

        explicit disjoint_sets(std::vector<std::vector<value_type>> sets) : disjoint_sets()
        {
            std::vector<std::vector<value_type>> sets_list;

            for(auto && set : sets)
            {
                std::unordered_set<value_type, hasher, value_equal> init_set(
                        set.begin(), set.end());

                sets_list.push_back(std::vector<value_type>(init_set.begin(), init_set.end()));
            }

            this->validate_duplicates(sets_list);

            for(auto && set : sets_list)
                for(auto && element : set)
                    this->represents.emplace(element, set[0]);

            this->size_ = sets_list.size();
        }

        disjoint_sets(std::initializer_list<std::initializer_list<value_type>> sets)
            : disjoint_sets()
        {
            std::vector<std::vector<value_type>> sets_list;

            for(auto && set : sets)
            {
                std::unordered_set<value_type, hasher, value_equal> init_set(
                        set.begin(), set.end());

                sets_list.push_back(std::vector<value_type>(init_set.begin(), init_set.end()));
            }

            this->validate_duplicates(sets_list);

            for(auto && set : sets_list)
                for(auto && element : set)
                    this->represents.emplace(element, set[0]);

            this->size_ = sets_list.size();
        }

        ~disjoint_sets() = default;
        disjoint_sets(const disjoint_sets & ds) = default;
        disjoint_sets(disjoint_sets && ds) noexcept = default;
        disjoint_sets & operator=(const disjoint_sets & ds) = default;
        disjoint_sets & operator=(disjoint_sets && ds) noexcept = default;

        /*!
         * \brief Gets the number of sets in this structure
         * \return the number of sets
         */
        size_type size() const
        {
            return this->size_;
        }

        /*!
         * \brief Checks whether this structure is empty.
         * \return \c true if the structure is empty, otherwise \c false
         */
        bool empty() const
        {
            return this->size_ == 0;
        }

        /*!
         * \brief Removes all sets from this structure.
         */
        void clear()
        {
            this->represents.clear();
            this->size_ = 0;
        }

        /*!
         * \brief Checks whether given element belongs to any set.
         * \param element the element
         * \return \c true if the element belongs to the structure, otherwise \c false
         */
        bool contains(const_reference element) const
        {
            return this->represents.find(element) != this->represents.end();
        }

        /*!
         * \brief Adds new elements as a new set.
         * \param elements the new elements
         * \throw std::invalid_argument if any of the elements is already present
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last);

        /*!
         * \brief Adds new elements to the existing set represented by another element.
         * \param elements the new elements
         * \param represent the represent of the set
         * \throw std::invalid_argument if any of the elements is already present
         * \throw std::out_of_range if the represent is not present
         */
        template <typename InputIterator>
        void insert(InputIterator first, InputIterator last, const_reference represent);

        /*!
         * \brief Adds new elements as a new set.
         * \param elements the new elements
         * \throw std::invalid_argument if any of the elements is already present
         */
        void insert(std::initializer_list<value_type> elements)
        {
            insert(elements.begin(), elements.end());
        }

        /*!
         * \brief Adds new elements to the existing set represented by another element.
         * \param elements the new elements
         * \param represent the represent of the set
         * \throw std::invalid_argument if any of the elements is already present
         * \throw std::out_of_range if the represent is not present
         */
        void insert(std::initializer_list<value_type> elements, const_reference represent)
        {
            insert(elements.begin(), elements.end(), represent);
        }

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element
         * \throw std::out_of_range if the element not present
         */
        const_reference operator[](const_reference element);

        /*!
         * \brief Finds represent of given element.
         * \param element the element
         * \return the represent of the element
         * \throw std::out_of_range if the element not present
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
         * \throw std::out_of_range if either element is not present
         */
        void union_set(const_reference element1, const_reference element2);

        /*!
         * \brief Checks whether given elements belong to the same set.
         * \param element1 the element from the first set
         * \param element2 the element from the second set
         * \return \c true if the elements are in the same set, otherwise \c false
         * \throw std::out_of_range if either element is not present
         */
        bool is_same_set(const_reference element1, const_reference element2);

        /*!
         * \brief Checks whether given elements belong to the same set.
         * \param element1 element from the first set
         * \param element2 element from the second set
         * \return \c true if the elements are in the same set, otherwise \c false
         * \throw std::out_of_range if either element is not present
         */
        bool is_same_set(const_reference element1, const_reference element2) const;

    private:
        void validate_duplicates(std::vector<std::vector<value_type>> sets_list);

        std::unordered_map<value_type, value_type, hasher, value_equal> represents;
        size_type size_;
    };

    template <typename E, typename Hash, typename Equal>
    template <typename InputIterator>
    void disjoint_sets<E, Hash, Equal>::insert(InputIterator first, InputIterator last)
    {
        std::vector<value_type> elements(first, last);

        for(auto && element : elements)
            if(this->contains(element))
                throw std::invalid_argument("Value already present.");

        for(auto && element : elements)
            this->represents.emplace(element, elements[0]);

        if(!elements.empty())
            ++size_;
    }

    template <typename E, typename Hash, typename Equal>
    template <typename InputIterator>
    void disjoint_sets<E, Hash, Equal>::insert(
            InputIterator first,
            InputIterator last,
            typename disjoint_sets<E, Hash, Equal>::const_reference represent)
    {
        std::vector<value_type> elements(first, last);

        for(auto && element : elements)
            if(this->contains(element))
                throw std::invalid_argument("Value already present.");

        if(!this->contains(represent))
            throw std::out_of_range("Represent value not present");

        for(auto && element : elements)
            this->represents.emplace(element, this->operator[](represent));
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

    template <typename E, typename Hash, typename Equal>
    void disjoint_sets<E, Hash, Equal>::validate_duplicates(
            std::vector<std::vector<typename disjoint_sets<E, Hash, Equal>::value_type>> sets_list)
    {
        std::vector<value_type> flattened;

        for(auto && set : sets_list)
            flattened.insert(flattened.end(), set.begin(), set.end());

        std::unordered_map<value_type, size_t, hasher, value_equal> counter;

        for(auto && element : flattened)
            ++counter[element];

        std::vector<value_type> duplicates;

        for(auto && entry : counter)
            if(entry.second > 1)
                duplicates.push_back(entry.first);

        if(!duplicates.empty())
            throw std::invalid_argument("Duplicate elements found");
    }
}

#endif
