/*!
 * \file vertex.hpp
 * \brief Structure of graph vertex
 */
#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

namespace algolib::graphs
{
    template <typename VertexId>
    class vertex;

    template <typename VertexId>
    bool operator==(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    bool operator!=(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    bool operator<(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    bool operator<=(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    bool operator>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    bool operator>=(const vertex<VertexId> & e1, const vertex<VertexId> & e2);

    template <typename VertexId>
    std::ostream & operator<<(std::ostream & os, const vertex<VertexId> & vertex);
}

namespace std
{
    template <typename VertexId>
    struct hash<algolib::graphs::vertex<VertexId>>;

    template <typename VertexId>
    struct hash<std::pair<algolib::graphs::vertex<VertexId>, algolib::graphs::vertex<VertexId>>>;
}

namespace algolib::graphs
{
    template <typename VertexId>
    class vertex
    {
    public:
        explicit vertex(VertexId id) : id_{id}
        {
        }

        ~vertex() = default;
        vertex(const vertex<VertexId> &) = default;
        vertex(vertex<VertexId> &&) = default;
        vertex<VertexId> & operator=(const vertex<VertexId> &) = default;
        vertex<VertexId> & operator=(vertex<VertexId> &&) = default;

        const VertexId & id() const
        {
            return id_;
        }

        // clang-format off
            friend bool operator== <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend bool operator!= <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend bool operator< <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend bool operator<= <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend bool operator> <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend bool operator>= <VertexId>(const vertex<VertexId> & e1, const vertex<VertexId> & e2);
            friend std::ostream & operator<< <VertexId>(std::ostream & os, const vertex<VertexId> & vertex);
        // clang-format on

        friend struct std::hash<vertex<VertexId>>;

    private:
        VertexId id_;
    };

    template <typename VertexId>
    bool operator==(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return e1.id_ == e2.id_;
    }

    template <typename VertexId>
    bool operator!=(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return !(e1 == e2);
    }

    template <typename VertexId>
    bool operator<(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return e1.id_ < e2.id_;
    }

    template <typename VertexId>
    bool operator<=(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return !(e2 < e1);
    }

    template <typename VertexId>
    bool operator>(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return e2 < e1;
    }

    template <typename VertexId>
    bool operator>=(const vertex<VertexId> & e1, const vertex<VertexId> & e2)
    {
        return !(e1 < e2);
    }

    template <typename VertexId>
    std::ostream & operator<<(std::ostream & os, const vertex<VertexId> & vertex)
    {
        os << "Vertex(" << vertex.id_ << ")";
        return os;
    }
}

namespace std
{
    template <typename VertexId>
    struct hash<algolib::graphs::vertex<VertexId>>
    {
        using argument_type = algolib::graphs::vertex<VertexId>;
        using result_type = size_t;

        result_type operator()(const argument_type & vertex) const
        {
            return std::hash<VertexId>()(vertex.id_);
        }
    };

    template <typename VertexId>
    struct hash<std::pair<algolib::graphs::vertex<VertexId>, algolib::graphs::vertex<VertexId>>>
    {
        using element_type = algolib::graphs::vertex<VertexId>;
        using argument_type = std::pair<element_type, element_type>;
        using result_type = size_t;

        result_type operator()(const argument_type & pair) const
        {
            result_type first_hash = std::hash<element_type>()(pair.first);
            result_type second_hash = std::hash<element_type>()(pair.second);

            return first_hash ^ (second_hash + 0x9e3779b9 + (first_hash << 6) + (first_hash >> 2));
        }
    };
}

#endif
