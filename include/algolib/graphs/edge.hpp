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
        template <typename Vertex = size_t>
        class edge;

        template <typename Vertex>
        bool operator==(const edge<Vertex> & e1, const edge<Vertex> & e2);

        template <typename Vertex>
        bool operator!=(const edge<Vertex> & e1, const edge<Vertex> & e2);

        template <typename Vertex>
        std::ostream & operator<<(std::ostream & os, const edge<Vertex> & edge);
    }
}

namespace std
{
    template <typename Vertex>
    struct hash<algolib::graphs::edge<Vertex>>;
}

namespace algolib
{
    namespace graphs
    {
        template <typename Vertex>
        class edge
        {
        public:
            edge(Vertex source, Vertex destination) : source_{source}, destination_{destination}
            {
            }

            ~edge() = default;
            edge(const edge<Vertex> &) = default;
            edge(edge<Vertex> &&) = default;
            edge<Vertex> & operator=(const edge<Vertex> &) = default;
            edge<Vertex> & operator=(edge<Vertex> &&) = default;

            const Vertex & source() const
            {
                return source_;
            }

            const Vertex & destination() const
            {
                return destination_;
            }

            Vertex get_neighbour(Vertex vertex) const
            {
                if(source_ == vertex)
                    return destination_;

                if(destination_ == vertex)
                    return source_;

                throw std::invalid_argument("Edge is not adjacent to the vertex");
            }

            edge<Vertex> reversed() const
            {
                return edge<Vertex>(destination_, source_);
            }

            friend bool operator==<Vertex>(const edge<Vertex> & e1, const edge<Vertex> & e2);
            friend bool operator!=<Vertex>(const edge<Vertex> & e1, const edge<Vertex> & e2);
            friend std::ostream & operator<<<Vertex>(std::ostream & os, const edge<Vertex> & edge);

            friend struct std::hash<edge<Vertex>>;

        private:
            Vertex source_;
            Vertex destination_;
        };

        template <typename Vertex>
        bool operator==(const edge<Vertex> & e1, const edge<Vertex> & e2)
        {
            return e1.source_ == e2.source_ && e1.destination_ == e2.destination_;
        }

        template <typename Vertex>
        bool operator!=(const edge<Vertex> & e1, const edge<Vertex> & e2)
        {
            return !(e1 == e2);
        }

        template <typename Vertex>
        std::ostream & operator<<(std::ostream & os, const edge<Vertex> & edge)
        {
            os << "Edge{" << edge.source_ << " -- " << edge.destination_ << "}";
            return os;
        }
    }
}

namespace std
{
    template <typename Vertex>
    struct hash<algolib::graphs::edge<Vertex>>
    {
        using argument_type = algolib::graphs::edge<Vertex>;
        using result_type = size_t;

        result_type operator()(const argument_type & edge)
        {
            result_type source_hash = std::hash<Vertex>()(edge.source_);
            result_type destination_hash = std::hash<Vertex>()(edge.destination_);

            return source_hash
                   ^ (destination_hash + 0x9e3779b9 + (source_hash << 6) + (source_hash >> 2));
        }
    };
}

#endif
