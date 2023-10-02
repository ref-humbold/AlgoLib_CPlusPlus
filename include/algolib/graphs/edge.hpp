/*!
 * \file edge.hpp
 * \brief Structure of graph edge.
 */
#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include "algolib/graphs/vertex.hpp"

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
        using vertex_type = vertex<VertexId>;

        edge(vertex_type source, vertex_type destination)
            : source_{source}, destination_{destination}
        {
        }

        ~edge() = default;
        edge(const edge<VertexId> &) = default;
        edge(edge<VertexId> &&) = default;
        edge<VertexId> & operator=(const edge<VertexId> &) = default;
        edge<VertexId> & operator=(edge<VertexId> &&) = default;

        const vertex_type & source() const
        {
            return source_;
        }

        const vertex_type & destination() const
        {
            return destination_;
        }

        /*!
         * \brief Gets the neighbour of given adjacent vertex.
         * \param vertex the vertex adjacent to this edge
         * \return the neighbour of the vertex along this edge
         * \throw std::invalid_argument if the vertex is not adjacent to this edge
         */
        const vertex_type & get_neighbour(const vertex<VertexId> & vertex) const
        {
            if(source_ == vertex)
                return destination_;

            if(destination_ == vertex)
                return source_;

            throw std::invalid_argument("Edge is not adjacent to the vertex");
        }

        //! \return the edge with reversed direction
        edge<VertexId> reversed() const
        {
            return edge<VertexId>(destination_, source_);
        }

        friend bool operator== <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend bool operator!= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend bool operator< <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend bool operator<= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend bool operator><VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend bool operator>= <VertexId>(const edge<VertexId> & e1, const edge<VertexId> & e2);
        friend std::ostream & operator<< <VertexId>(std::ostream & os, const edge<VertexId> & edge);

        friend struct std::hash<edge<VertexId>>;

    private:
        vertex_type source_, destination_;
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
            result_type source_hash =
                    std::hash<typename argument_type::vertex_type>()(edge.source_);
            result_type destination_hash =
                    std::hash<typename argument_type::vertex_type>()(edge.destination_);

            return source_hash
                   ^ (destination_hash + 0x9e3779b9 + (source_hash << 6) + (source_hash >> 2));
        }
    };
}

#endif
