/*!
 * \file edge.hpp
 * \brief Structure of graph edge
 */
#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace algolib
{
    namespace graphs
    {
        template <typename V>
        class edge;

        template <typename V>
        bool operator==(const edge<V> & e1, const edge<V> & e2);

        template <typename V>
        bool operator!=(const edge<V> & e1, const edge<V> & e2);

        template <typename V>
        std::ostream & operator<<(std::ostream & os, const edge<V> & edge);
    }
}

namespace std
{
    template <typename V>
    struct hash<algolib::graphs::edge<V>>;
}

namespace algolib
{
    namespace graphs
    {
        template <typename V>
        class edge
        {
        public:
            edge(V source, V destination) : source_{source}, destination_{destination}
            {
            }

            ~edge() = default;
            edge(const edge<V> &) = default;
            edge(edge<V> &&) = default;
            edge<V> & operator=(const edge<V> &) = default;
            edge<V> & operator=(edge<V> &&) = default;

            const V & source() const
            {
                return source_;
            }

            const V & destination() const
            {
                return destination_;
            }

            V get_neighbour(V vertex) const
            {
                if(source_ == vertex)
                    return destination_;

                if(destination_ == vertex)
                    return source_;

                throw std::invalid_argument("Edge is not adjacent to the vertex");
            }

            edge<V> reversed() const
            {
                return edge<V>(destination_, source_);
            }

            friend bool operator==<V>(const edge<V> & e1, const edge<V> & e2);
            friend bool operator!=<V>(const edge<V> & e1, const edge<V> & e2);
            friend std::ostream & operator<<<V>(std::ostream & os, const edge<V> & edge);

            friend struct std::hash<edge<V>>;

        private:
            V source_;
            V destination_;
        };

        template <typename V>
        bool operator==(const edge<V> & e1, const edge<V> & e2)
        {
            return e1.source_ == e2.source_ && e1.destination_ == e2.destination_;
        }

        template <typename V>
        bool operator!=(const edge<V> & e1, const edge<V> & e2)
        {
            return !(e1 == e2);
        }

        template <typename V>
        std::ostream & operator<<(std::ostream & os, const edge<V> & edge)
        {
            os << "Edge{" << edge.source_ << " -- " << edge.destination_ << "}";
            return os;
        }
    }
}

namespace std
{
    template <typename V>
    struct hash<algolib::graphs::edge<V>>
    {
        using argument_type = algolib::graphs::edge<V>;
        using result_type = size_t;

        result_type operator()(const argument_type & edge)
        {
            result_type source_hash = std::hash<V>()(edge.source_);
            result_type destination_hash = std::hash<V>()(edge.destination_);

            return source_hash
                   ^ (destination_hash + 0x9e3779b9 + (source_hash << 6) + (source_hash >> 2));
        }
    };
}

#endif
