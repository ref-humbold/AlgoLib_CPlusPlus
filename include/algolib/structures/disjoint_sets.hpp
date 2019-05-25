/*!
 * \file disjoint_sets.hpp
 * \brief Disjoint sets structure (union-find).
 */
#ifndef DISJOINT_SETS_HPP_
#define DISJOINT_SETS_HPP_

#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <unordered_map>
#include <vector>

namespace algolib
{
    namespace structures
    {
        template <typename E>
        class disjoint_sets
        {
        public:
            disjoint_sets() : sets{0}
            {
            }

            explicit disjoint_sets(std::initializer_list<E> universe) : sets{universe.size()}
            {
                for(E e : universe)
                    represents.emplace(e, e);
            }

            template <typename InputIterator>
            disjoint_sets(InputIterator first, InputIterator last);

            ~disjoint_sets() = default;
            disjoint_sets(const disjoint_sets & ds) = default;
            disjoint_sets(disjoint_sets && ds) noexcept = default;
            disjoint_sets & operator=(const disjoint_sets & ds) = default;
            disjoint_sets & operator=(disjoint_sets && ds) noexcept = default;

            /// \return number of sets
            size_t size() const
            {
                return sets;
            }

            /*!
             * \brief Checks whether given element in one of the sets in the structure.
             * \param element element
             * \return  true if element belongs to the structure, otherwise false
             */
            bool contains(const E & element) const
            {
                return represents.find(element) != represents.end();
            }

            /*!
             * \brief Adds new element to the set represented by another element.
             * \param element new element
             * \param repr representant of the set
             */
            void insert(const E & element, const E & repr);

            /*!
             * \brief Adds new element as a singleton set.
             * \param element new element
             */
            void insert(const E & element);

            /*!
             * \brief Adds new elements to the set represented by another element.
             * \param first beginning of elements range
             * \param last end of elements range
             * \param repr representant of the set
             */
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last, const E & repr);

            /*!
             * \brief Adds new elements as singleton sets.
             * \param first beginning of elements range
             * \param last end of elements range
             */
            template <typename InputIterator>
            void insert(InputIterator first, InputIterator last);

            /*!
             * \brief Finds represent of the set with given element
             * \param element element from the structure
             * \return represent of the element
             */
            const E & find_set(const E & element);

            /*!
             * \brief Finds represent of the set with given element
             * \param element element from the structure
             * \return represent of the element
             */
            const E & find_set(const E & element) const;

            /*!
             * \brief Finds represent of the set with given element
             * \param element element from the structure
             * \return represent of the element
             */
            const E & operator[](const E & element)
            {
                return find_set(element);
            }

            /*!
             * \brief Finds represent of the set with given element
             * \param element element from the structure
             * \return represent of the element
             */
            const E & operator[](const E & element) const
            {
                return find_set(element);
            }

            /*!
             * \brief Performs union of two sets in the structure.
             * \param element1 element from the first set
             * \param element2 element from the second set
             */
            void union_set(const E & element1, const E & element2);

            /*!
             * \brief Tests whether two elements belong to the same set
             * \param element1 element from the first set
             * \param element2 element from the second set
             * \return true if both element are in the same set, otherwise false
             */
            bool is_same_set(const E & element1, const E & element2);

            /*!
             * \brief Tests whether two elements belong to the same set
             * \param element1 element from the first set
             * \param element2 element from the second set
             * \return true if both element are in the same set, otherwise false
             */
            bool is_same_set(const E & element1, const E & element2) const;

        private:
            std::unordered_map<E, E> represents;  //!< Map of elements' represents.
            size_t sets;  //!< Number of sets.
        };

        template <typename E>
        template <typename InputIterator>
        disjoint_sets<E>::disjoint_sets(InputIterator first, InputIterator last) : sets{0}
        {
            for(InputIterator it = first; it != last; ++it)
            {
                represents.emplace(*it, *it);
                ++sets;
            }
        }

        template <typename E>
        void disjoint_sets<E>::insert(const E & element, const E & repr)
        {
            if(contains(element))
                throw std::invalid_argument("New value already present");

            if(!contains(repr))
                throw std::invalid_argument("Represent value not present");

            represents.emplace(element, find_set(repr));
        }

        template <typename E>
        void disjoint_sets<E>::insert(const E & element)
        {
            if(contains(element))
                throw std::invalid_argument("New value already present");

            represents.emplace(element, element);
            sets++;
        }

        template <typename E>
        template <typename InputIterator>
        void disjoint_sets<E>::insert(InputIterator first, InputIterator last)
        {
            for(InputIterator it = first; it != last; ++it)
                if(contains(*it))
                    throw std::invalid_argument("New value already present");

            for(InputIterator it = first; it != last; ++it)
            {
                represents.emplace(*it, *it);
                sets++;
            }
        }

        template <typename E>
        template <typename InputIterator>
        void disjoint_sets<E>::insert(InputIterator first, InputIterator last, const E & repr)
        {
            for(InputIterator it = first; it != last; ++it)
                if(contains(*it))
                    throw std::invalid_argument("New value already present");

            for(InputIterator it = first; it != last; ++it)
                represents.emplace(*it, find_set(repr));
        }

        template <typename E>
        const E & disjoint_sets<E>::find_set(const E & element)
        {
            if(represents.at(element) != element)
                represents[element] = find_set(represents[element]);

            return represents.at(element);
        }

        template <typename E>
        const E & disjoint_sets<E>::find_set(const E & element) const
        {
            return represents.at(element) == element ? element : find_set(represents.at(element));
        }

        template <typename E>
        void disjoint_sets<E>::union_set(const E & element1, const E & element2)
        {
            if(is_same_set(element1, element2))
                return;

            represents[find_set(element1)] = find_set(element2);
            --sets;
        }

        template <typename E>
        bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2)
        {
            return find_set(element1) == find_set(element2);
        }

        template <typename E>
        bool disjoint_sets<E>::is_same_set(const E & element1, const E & element2) const
        {
            return find_set(element1) == find_set(element2);
        }
    }
}

#endif
