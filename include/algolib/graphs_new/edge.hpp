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
#include "vertex.hpp"

namespace algolib::graphs
{
    template <typename VertexId>
    class edge;

    template <typename VertexId>
    bool operator==(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    bool operator!=(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    bool operator<(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    bool operator<=(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    bool operator>(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    bool operator>=(const edge<VertexId> & e1, const edge<VertexId> & e2);

    template <typename VertexId>
    std::ostream & operator<<(std::ostream & os, const edge<VertexId> & edge);
}

namespace std
{
    template <typename VertexId>
    struct hash<algolib::graphs::edge<VertexId>>;
}

namespace algolib::graphs
{
    template <typename VertexId>
    class edge
    {
    public:
        edge(vertex<VertexId> source, vertex<VertexId> destination)
            : source_{source}, destination_{destination}
        {
        }

        ~edge() = default;
        edge(const edge<VertexId> &) = default;
        edge(edge<VertexId> &&) = default;
        edge<VertexId> & operator=(const edge<VertexId> &) = default;
        edge<VertexId> & operator=(edge<VertexId> &&) = default;

        const vertex<VertexId> & source() const
        {
            return source_;
        }

        const vertex<VertexId> & destination() const
        {
            return destination_;
        }

        vertex<VertexId> get_neighbour(const vertex<VertexId> & vertex) const
        {
            if(source_ == vertex)
                return destination_;

            if(destination_ == vertex)
                return source_;

            throw std::invalid_argument("Edge is not adjacent to the vertex");
        }

        edge<VertexId> reversed() const
        {
            return edge<VertexId>(destination_, source_);
        }

        // clang-format off
            friend bool operator== <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend bool operator!= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend bool operator< <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend bool operator<= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend bool operator> <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend bool operator>= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
            friend std::ostream & operator<< <VertexId>(std::ostream & os, const edge<VertexId> & edge);
        // clang-format on

        friend struct std::hash<edge<VertexId>>;

    private:
        vertex<VertexId> source_, destination_;
    };

    template <typename VertexId>
    bool operator==(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return e1.source_ == e2.source_ && e1.destination_ == e2.destination_;
    }

    template <typename VertexId>
    bool operator!=(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return !(e1 == e2);
    }

    template <typename VertexId>
    bool operator<(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return e1.source_ < e2.source_
               || (!(e2.source_ < e1.source_) && e1.destination_ < e2.destination_);
    }

    template <typename VertexId>
    bool operator<=(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return !(e2 < e1);
    }

    template <typename VertexId>
    bool operator>(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return e2 < e1;
    }

    template <typename VertexId>
    bool operator>=(const edge<VertexId> & e1, const edge<VertexId> & e2)
    {
        return !(e1 < e2);
    }

    template <typename VertexId>
    std::ostream & operator<<(std::ostream & os, const edge<VertexId> & edge)
    {
        os << "Edge{" << edge.source_ << " -- " << edge.destination_ << "}";
        return os;
    }
}

namespace std
{
    template <typename VertexId>
    struct hash<algolib::graphs::edge<VertexId>>
    {
        using argument_type = algolib::graphs::edge<VertexId>;
        using result_type = size_t;

        result_type operator()(const argument_type & edge) const
        {
            result_type source_hash = std::hash<VertexId>()(edge.source_);
            result_type destination_hash = std::hash<VertexId>()(edge.destination_);

            return source_hash
                   ^ (destination_hash + 0x9e3779b9 + (source_hash << 6) + (source_hash >> 2));
        }
    };
}

#endif
