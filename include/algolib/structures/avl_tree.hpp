/**
 * @file avl_tree.hpp
 * @brief AVL tree structure.
 */
#ifndef AVL_TREE_HPP_
#define AVL_TREE_HPP_

#include <cstdlib>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <functional>

namespace algolib
{
    namespace structures
    {
#pragma region avl_tree

        template <typename E, typename C = std::less<E>>
        class avl_tree
        {
        private:
            class avl_node;
            class avl_inner_node;
            class avl_header_node;

            class avl_iterator;
            class avl_succ_iterator;
            class avl_pred_iterator;

            using node_ptr = avl_node *;
            using inner_ptr = avl_inner_node *;
            using header_ptr = avl_header_node *;

        public:
            using iterator = avl_succ_iterator;
            using reverse_iterator = avl_pred_iterator;

            explicit avl_tree(const C & cmp = C()) : cmp{cmp}
            {
            }

            avl_tree(std::initializer_list<E> init_list, const C & cmp = C()) : cmp{cmp}
            {
                for(auto i : init_list)
                    insert(i);
            }

            ~avl_tree()
            {
                delete this->tree;
            }

            avl_tree(const avl_tree & avl)
                : tree{avl_tree::clone_node(avl.tree)}, elems{avl.elems}, cmp{avl.cmp}
            {
            }

            avl_tree(avl_tree && avl) noexcept : elems{std::move(avl.elems)}, cmp{avl.cmp}
            {
                std::swap(this->tree, avl.tree);
            }

            avl_tree<E, C> & operator=(const avl_tree<E, C> & avl);
            avl_tree<E, C> & operator=(avl_tree<E, C> && avl) noexcept;

            /// @return iterator na początku
            iterator begin() const;

            /// @return iterator na końcu
            iterator end() const;

            /// @return odwrócony iterator na początku
            reverse_iterator rbegin() const;

            /// @return odwrócony iterator na końcu
            reverse_iterator rend() const;

            /// @return liczba elemenów drzewa
            size_t size() const
            {
                return elems;
            }

            /// @return czy drzewo jest puste
            bool empty() const
            {
                return get_root() == nullptr;
            }

            /**
             * Sprawdzanie występowania elementu w drzewie.
             * @param element wartość do znalezienia
             * @return iterator na wartość w drzewie
             */
            iterator find(const E & element) const;

            /**
             * Dodawanie elementu do drzewa.
             * @param element wartość do dodania
             * @return iterator na nowy element z infromacją o jego dodaniu
             */
            std::pair<iterator, bool> insert(const E & element);

            /**
             * Usuwanie elementu z drzewa.
             * @param element wartość do usunięcia
             */
            void erase(const E & element);

            /// Usuwanie wszystkich elementów z drzewa.
            void clear();

        private:
            /**
             * Kopiowanie obiektu węzła.
             * @return kopia obiektu
             */
            static node_ptr clone_node(node_ptr node)
            {
                return node == nullptr ? nullptr : node->clone();
            }

            /**
             * Usuwanie elementu z pamięci.
             * @param node węzeł do usunięcia
             */
            void destroy_node(node_ptr node)
            {
                node->set_left(nullptr);
                node->set_right(nullptr);
                --elems;
                delete node;
            }

            /// @return wewnętrzny korzeń drzewa
            node_ptr get_root() const
            {
                return tree->get_parent();
            }

            /// @param node węzeł, który zostanie wewnętrznym korzeniem
            void set_root(node_ptr node)
            {
                tree->set_parent(node);
            }

            /**
             * Sprawdzanie, czy węzeł jest wewnętrznym korzeniem.
             * @param node węzeł
             * @return czy węzeł to korzeń
             */
            bool is_root(node_ptr node)
            {
                return node->get_parent()->get_height() == 0;
            }

            /**
             * Wskazanie poddrzewa, w którym może znaleźć się element.
             * @param node węzeł
             * @param element element
             * @return korzeń poddrzewa z elementem
             */
            node_ptr search(node_ptr node, const E & element) const;

            /**
             * Wyszukiwanie ojca węzła z daną wartością.
             * @param element wartość do znalezienia
             * @return ojciec węzła z wartością
             */
            node_ptr find_node_parent(const E & element) const;

            /**
             * Usuwanie elementu z korzenia drzewa.
             * @param root korzeń drzewa
             */
            void delete_root(node_ptr root);

            /**
             * Usuwanie elementu z węzła wewnętrznego drzewa.
             * @param node węzeł do usunięcia
             */
            void delete_node(node_ptr node);

            /**
             * Zamiana poddrzewa ukorzenionego w danym węźle.
             * @param node1 węzeł do zamiany
             * @param node2 korzeń nowego poddrzewa
             */
            void replace_subtree(node_ptr node1, node_ptr node2);

            /**
             * Rotowanie węzła wzdłuż krawędzi z jego ojcem.
             * @param node węzeł do rotacji
             */
            void rotate(node_ptr node);

            /**
             * Przywracanie balansowania na ścieżce od wierzchołka do korzenia.
             * @param node wierzchołek początkowy
             */
            void balance(node_ptr node);

            /**
             * Wyliczanie balansu wierzchołka.
             * @param node węzeł
             * @return wartość balansu
             */
            int count_balance(node_ptr node);

            /// Korzeń drzewa.
            node_ptr tree = new avl_header_node();

            ///  Liczba elementów drzewa.
            size_t elems = 0;

            /// Komparator
            C cmp;
        };

        template <typename E, typename C>
        avl_tree<E, C> & avl_tree<E, C>::operator=(const avl_tree<E, C> & avl)
        {
            node_ptr tree_orig = this->tree;

            this->elems = avl.elems;
            this->cmp = avl.cmp;
            this->tree = avl_tree::clone_node(avl.tree);
            delete tree_orig;

            return *this;
        }

        template <typename E, typename C>
        avl_tree<E, C> & avl_tree<E, C>::operator=(avl_tree<E, C> && avl) noexcept
        {
            std::swap(this->tree, avl.tree);
            std::swap(this->elems, avl.elems);
            std::swap(this->cmp, avl.cmp);

            return *this;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::iterator avl_tree<E, C>::begin() const
        {
            return iterator(get_root()->minimum());
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::iterator avl_tree<E, C>::end() const
        {
            return iterator(tree);
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::reverse_iterator avl_tree<E, C>::rbegin() const
        {
            return reverse_iterator(get_root()->maximum());
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::reverse_iterator avl_tree<E, C>::rend() const
        {
            return reverse_iterator(tree);
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::iterator avl_tree<E, C>::find(const E & element) const
        {
            if(empty())
                return end();

            avl_tree<E, C>::node_ptr node_parent = find_node_parent(element);

            if(node_parent == nullptr)
                return iterator(get_root());

            avl_tree<E, C>::node_ptr the_node = search(node_parent, element);

            if(the_node == nullptr)
                return end();

            return iterator(the_node);
        }

        template <typename E, typename C>
        std::pair<typename avl_tree<E, C>::iterator, bool> avl_tree<E, C>::insert(const E & element)
        {
            avl_tree<E, C>::node_ptr node_parent = find_node_parent(element);
            avl_tree<E, C>::node_ptr the_node =
                    node_parent == nullptr ? get_root() : search(node_parent, element);

            if(the_node != nullptr)
                return std::make_pair(iterator(the_node), false);

            avl_tree<E, C>::node_ptr new_node = new avl_inner_node(element);

            if(node_parent != nullptr)
            {
                if(cmp(element, node_parent->get_element()))
                    node_parent->set_left(new_node);
                else
                    node_parent->set_right(new_node);

                balance(node_parent);
            }
            else
                set_root(new_node);

            ++elems;

            return std::make_pair(iterator(new_node), true);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::erase(const E & element)
        {
            avl_tree<E, C>::node_ptr node_parent = find_node_parent(element);
            avl_tree<E, C>::node_ptr the_node =
                    node_parent == nullptr ? get_root() : search(node_parent, element);

            if(the_node == nullptr)
                return;

            if(node_parent == nullptr)
                delete_root(the_node);
            else
                delete_node(the_node);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::clear()
        {
            delete get_root();
            set_root(nullptr);
            elems = 0;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr avl_tree<E, C>::search(avl_tree<E, C>::node_ptr node,
                                                                 const E & element) const
        {
            if(!cmp(element, node->get_element()) && !cmp(node->get_element(), element))
                return node;

            if(cmp(element, node->get_element()))
                return node->get_left();

            return node->get_right();
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr avl_tree<E, C>::find_node_parent(const E & element) const
        {
            typename avl_tree<E, C>::node_ptr tree_iter = get_root();
            typename avl_tree<E, C>::node_ptr iter_parent = nullptr;

            while(tree_iter != nullptr
                  && (cmp(tree_iter->get_element(), element)
                      || cmp(element, tree_iter->get_element())))
            {
                iter_parent = tree_iter;
                tree_iter = search(tree_iter, element);
            }

            return iter_parent;
        }

        template <typename E, typename C>
        void avl_tree<E, C>::delete_root(avl_tree<E, C>::node_ptr root)
        {
            if(root->get_left() != nullptr && root->get_right() != nullptr)
                delete_node(root);
            else
            {
                node_ptr new_root =
                        root->get_left() != nullptr ? root->get_left() : root->get_right();

                set_root(new_root);
                destroy_node(root);
            }
        }

        template <typename E, typename C>
        void avl_tree<E, C>::delete_node(avl_tree<E, C>::node_ptr node)
        {
            if(node->get_left() != nullptr && node->get_right() != nullptr)
            {
                avl_tree<E, C>::node_ptr succ = node->get_right()->minimum();

                std::swap(succ->get_element(), node->get_element());
                delete_node(succ);
            }
            else
            {
                avl_tree<E, C>::node_ptr son =
                        node->get_left() != nullptr ? node->get_left() : node->get_right();
                avl_tree<E, C>::node_ptr node_parent = node->get_parent();

                replace_subtree(node, son);
                balance(node_parent);
                destroy_node(node);
            }
        }

        template <typename E, typename C>
        void avl_tree<E, C>::replace_subtree(avl_tree<E, C>::node_ptr node1,
                                             avl_tree<E, C>::node_ptr node2)
        {
            if(is_root(node1))
                set_root(node2);
            else if(node1->is_left_son())
                node1->get_parent()->set_left(node2);
            else if(node1->is_right_son())
                node1->get_parent()->set_right(node2);

            node1->set_parent(nullptr);
        }

        template <typename E, typename C>
        void avl_tree<E, C>::rotate(avl_tree<E, C>::node_ptr node)
        {
            if(is_root(node))
                return;

            avl_tree<E, C>::node_ptr upper_node = node->get_parent();

            if(node->is_right_son())
            {
                upper_node->set_right(node->get_left());
                replace_subtree(upper_node, node);
                node->set_left(upper_node);
            }
            else if(node->is_left_son())
            {
                upper_node->set_left(node->get_right());
                replace_subtree(upper_node, node);
                node->set_right(upper_node);
            }
        }

        template <typename E, typename C>
        void avl_tree<E, C>::balance(avl_tree<E, C>::node_ptr node)
        {
            while(node->get_height() > 0)
            {
                node->count_height();

                int new_balance = count_balance(node);

                if(new_balance >= 2)
                {
                    if(count_balance(node->get_left()) > 0)
                        rotate(node->get_left());
                    else if(count_balance(node->get_left()) < 0)
                    {
                        rotate(node->get_left()->get_right());
                        rotate(node->get_left());
                    }
                }
                else if(new_balance <= -2)
                {
                    if(count_balance(node->get_right()) < 0)
                        rotate(node->get_right());
                    else if(count_balance(node->get_right()) > 0)
                    {
                        rotate(node->get_right()->get_left());
                        rotate(node->get_right());
                    }
                }

                node = node->get_parent();
            }
        }

        template <typename E, typename C>
        int avl_tree<E, C>::count_balance(avl_tree<E, C>::node_ptr node)
        {
            int left_height = node->get_left() == nullptr ? 0 : node->get_left()->get_height();
            int right_height = node->get_right() == nullptr ? 0 : node->get_right()->get_height();

            return left_height - right_height;
        }

#pragma endregion
#pragma region avl_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_node
        {
        public:
            avl_node() = default;
            virtual ~avl_node() = default;
            avl_node(const avl_node & node) = default;
            avl_node(avl_node && node) = delete;
            avl_node & operator=(const avl_node & node) = default;
            avl_node & operator=(avl_node && node) = delete;

            virtual size_t get_height() = 0;

            virtual node_ptr get_left() = 0;

            virtual void set_left(node_ptr node) = 0;

            virtual node_ptr get_right() = 0;

            virtual void set_right(node_ptr node) = 0;

            virtual node_ptr get_parent() = 0;

            virtual void set_parent(node_ptr node) = 0;

            /**
             * Kopiowanie obiektu węzła.
             * @return kopia obiektu
             */
            virtual node_ptr clone() = 0;

            /**
             * Sprawdzanie, czy węzeł jest lewym synem.
             * @return czy węzeł to lewy syn
             */
            virtual bool is_left_son() = 0;

            /**
             * Sprawdzanie, czy węzeł jest prawym synem.
             * @return czy węzeł to prawy syn
             */
            virtual bool is_right_son() = 0;

            /// Wyliczanie wysokości wierzchołka.
            virtual void count_height() = 0;

            /**
             * Wyszukiwanie minimum w poddrzewie.
             * @return węzeł z minimalną wartością w poddrzewie
             */
            virtual node_ptr minimum() = 0;

            /**
             * Wyszukiwanie maksimum w ukorzenionym poddrzewie.
             * @return węzeł z maksymalną wartością w poddrzewie
             */
            virtual node_ptr maximum() = 0;
        };

#pragma endregion
#pragma region avl_inner_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_inner_node : public avl_tree<E, C>::avl_node
        {
        public:
            explicit avl_inner_node(const E & elem) : avl_tree<E, C>::avl_node(), element{elem}
            {
            }

            ~avl_inner_node();
            avl_inner_node(const avl_inner_node & node);
            avl_inner_node(avl_inner_node && node) = delete;
            avl_inner_node & operator=(const avl_inner_node & node);
            avl_inner_node & operator=(avl_inner_node && node) = delete;

            E & get_element()
            {
                return element;
            }

            size_t get_height() override
            {
                return this->height;
            }

            node_ptr get_left() override
            {
                return this->left;
            }

            void set_left(node_ptr node) override
            {
                this->left = node;

                if(this->left != nullptr)
                    this->left->set_parent(this);

                count_height();
            }

            node_ptr get_right() override
            {
                return this->right;
            }

            void set_right(node_ptr node) override
            {
                this->right = node;

                if(this->right != nullptr)
                    this->right->set_parent(this);

                count_height();
            }

            node_ptr get_parent() override
            {
                return this->parent;
            }

            void set_parent(node_ptr node) override
            {
                this->parent = node;
            }

            node_ptr clone() override
            {
                return new avl_inner_node(*this);
            }

            bool is_left_son();

            bool is_right_son();

            void count_height() override;

            node_ptr minimum() override;

            node_ptr maximum() override;

        private:
            /// Wartość w węźle.
            E element;

            /// Wysokość węzła.
            int height = 1;

            /// Lewy syn węzła.
            node_ptr left = nullptr;

            /// Prawy syn węzła.
            node_ptr right = nullptr;

            /// Ojciec węzła.
            node_ptr parent = nullptr;
        };

        template <typename E, typename C>
        avl_tree<E, C>::avl_inner_node::~avl_inner_node()
        {
            delete this->left;
            delete this->right;
        }

        template <typename E, typename C>
        avl_tree<E, C>::avl_inner_node::avl_inner_node(const avl_tree<E, C>::avl_inner_node & node)
            : avl_tree<E, C>::avl_node(), element{node.element}, height{node.height}
        {
            this->set_left(avl_tree::clone_node(node.left));
            this->set_right(avl_tree::clone_node(node.right));
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_inner_node & avl_tree<E, C>::avl_inner_node::
                operator=(const avl_tree<E, C>::avl_inner_node & node)
        {
            node_ptr left_orig = this->left;
            node_ptr right_orig = this->right;

            this->element = node.element;
            this->height = node.height;
            this->set_left(clone_node(node.left));
            this->set_right(clone_node(node.right));
            delete left_orig;
            delete right_orig;

            return *this;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_inner_node::is_left_son()
        {
            return parent != nullptr && parent->get_left() == this;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_inner_node::is_right_son()
        {
            return parent != nullptr && parent->get_right() == this;
        }

        template <typename E, typename C>
        void avl_tree<E, C>::avl_inner_node::count_height()
        {
            int left_height = left == nullptr ? 0 : left->get_height();
            int right_height = right == nullptr ? 0 : right->get_height();

            height = std::max(left_height, right_height) + 1;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr avl_tree<E, C>::avl_inner_node::minimum()
        {
            return left == nullptr ? this : left->minimum();
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr avl_tree<E, C>::avl_inner_node::maximum()
        {
            return right == nullptr ? this : right->maximum();
        }

#pragma endregion
#pragma region avl_root_node

        template <typename E, typename C>
        class avl_tree<E, C>::avl_header_node : public avl_tree<E, C>::avl_node
        {
        public:
            avl_header_node() : avl_tree<E, C>::avl_node()
            {
            }

            ~avl_header_node()
            {
                delete this->inner;
            }

            avl_header_node(const avl_header_node & node) : avl_tree<E, C>::avl_node()
            {
                this->set_parent(avl_tree::clone_node(node.inner));
            }

            avl_header_node(avl_header_node && node) = delete;
            avl_header_node & operator=(const avl_header_node & node);
            avl_header_node & operator=(avl_header_node && node) = delete;

            size_t get_height() override
            {
                return 0;
            }

            node_ptr get_left() override
            {
                return nullptr;
            }

            void set_left(node_ptr) override
            {
            }

            node_ptr get_right() override
            {
                return nullptr;
            }

            void set_right(node_ptr) override
            {
            }

            node_ptr get_parent() override
            {
                return inner;
            }

            void set_parent(node_ptr node) override
            {
                inner = node;

                if(inner != nullptr)
                    inner->set_parent(this);
            }

            node_ptr clone() override
            {
                return new avl_header_node(*this);
            }

            bool is_left_son() override
            {
                return false;
            }

            bool is_right_son() override
            {
                return false;
            }

            void count_height() override
            {
            }

            node_ptr minimum() override
            {
                return this;
            }

            node_ptr maximum() override
            {
                return this;
            }

        private:
            /// Wewnętrzne wierzchołki.
            node_ptr inner = nullptr;
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_header_node & avl_tree<E, C>::avl_header_node::
                operator=(const avl_tree<E, C>::avl_header_node & node)
        {
            node_ptr inner_orig = this->inner;

            this->set_parent(avl_tree::clone_node(node.inner));
            delete inner_orig;

            return *this;
        }

#pragma endregion
#pragma region avl_iterator

        template <typename E, typename C>
        class avl_tree<E, C>::avl_iterator
        {
        public:
            explicit avl_iterator(avl_tree<E, C>::node_ptr node) : current_node{node}
            {
            }

            /**
             * Dereferencja iteratora.
             * @return wartość w iteratorze
             */
            E & operator*() const;

            /**
             * Uzyskanie składowej spod iteratora.
             * @return wartość w iteratorze
             */
            E * operator->() const;

            /**
             * Porównanie iteratorów na równość.
             * @return czy iteratory wskazują na ten sam węzeł
             */
            bool operator==(const avl_iterator & it) const;

            /**
             * Porównanie iteratorów na różność.
             * @return czy iteratory wskazują na różne węzły
             */
            bool operator!=(const avl_iterator & it) const;

        protected:
            /**
             * Wyznaczanie następnika węzła w drzewie.
             * @param node węzeł
             * @return węzeł z następną wartością
             */
            avl_tree<E, C>::node_ptr successor(avl_tree<E, C>::node_ptr node);

            /**
             * Wyznaczanie poprzednika węzła w drzewie.
             * @param node węzeł
             * @return węzeł z poprzednią wartością
             */
            avl_tree<E, C>::node_ptr predecessor(avl_tree<E, C>::node_ptr node);

            /// Aktualny węzeł.
            avl_tree<E, C>::node_ptr current_node;
        };

        template <typename E, typename C>
        E & avl_tree<E, C>::avl_iterator::operator*() const
        {
            return this->current_node->get_element();
        }

        template <typename E, typename C>
        E * avl_tree<E, C>::avl_iterator::operator->() const
        {
            return &this->current_node->get_element();
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_iterator::operator==(const avl_tree<E, C>::avl_iterator & it) const
        {
            return this->current_node == it.current_node;
        }

        template <typename E, typename C>
        bool avl_tree<E, C>::avl_iterator::operator!=(const avl_tree<E, C>::avl_iterator & it) const
        {
            return this->current_node != it.current_node;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr
                avl_tree<E, C>::avl_iterator::successor(avl_tree<E, C>::node_ptr node)
        {
            avl_tree<E, C>::node_ptr succ = node;

            if(node->get_right() != nullptr)
                return node->get_right()->minimum();

            while(succ->get_height() > 0 && !succ->is_left_son())
                succ = succ->get_parent();

            return succ->get_height() <= 0 ? succ : succ->get_parent();
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::node_ptr
                avl_tree<E, C>::avl_iterator::predecessor(avl_tree<E, C>::node_ptr node)
        {
            avl_tree<E, C>::node_ptr pred = node;

            if(node->get_left() != nullptr)
                return node->get_left()->maximum();

            while(pred->get_height() > 0 && !pred->is_right_son())
                pred = pred->get_parent();

            return pred->get_height() <= 0 ? pred : pred->get_parent();
        }

#pragma endregion
#pragma region avl_succ_iterator

        template <typename E, typename C>
        class avl_tree<E, C>::avl_succ_iterator : public avl_tree<E, C>::avl_iterator
        {
        public:
            explicit avl_succ_iterator(avl_tree<E, C>::node_ptr node) : avl_iterator(node)
            {
            }

            avl_succ_iterator & operator++();

            const avl_succ_iterator operator++(int);

            avl_succ_iterator & operator--();

            const avl_succ_iterator operator--(int);
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_succ_iterator & avl_tree<E, C>::avl_succ_iterator::operator++()
        {
            if(this->current_node->get_height() > 0)
                this->current_node = this->successor(this->current_node);

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_succ_iterator avl_tree<E, C>::avl_succ_iterator::
                operator++(int)
        {
            avl_tree<E, C>::avl_succ_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_succ_iterator & avl_tree<E, C>::avl_succ_iterator::operator--()
        {
            this->current_node = this->current_node->get_height() > 0
                                         ? this->predecessor(this->current_node)
                                         : this->current_node->get_parent()->maximum();

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_succ_iterator avl_tree<E, C>::avl_succ_iterator::
                operator--(int)
        {
            avl_tree<E, C>::avl_iterator result = *this;

            --(*this);

            return result;
        }

#pragma endregion
#pragma region avl_pred_iterator

        template <typename E, typename C>
        class avl_tree<E, C>::avl_pred_iterator : public avl_tree<E, C>::avl_iterator
        {
        public:
            explicit avl_pred_iterator(avl_tree<E, C>::node_ptr node) : avl_iterator(node)
            {
            }

            avl_pred_iterator & operator++();

            const avl_pred_iterator operator++(int);

            avl_pred_iterator & operator--();

            const avl_pred_iterator operator--(int);
        };

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_pred_iterator & avl_tree<E, C>::avl_pred_iterator::operator++()
        {
            if(this->current_node->get_height() > 0)
                this->current_node = this->predecessor(this->current_node);

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_pred_iterator avl_tree<E, C>::avl_pred_iterator::
                operator++(int)
        {
            avl_tree<E, C>::avl_pred_iterator result = *this;

            ++(*this);

            return result;
        }

        template <typename E, typename C>
        typename avl_tree<E, C>::avl_pred_iterator & avl_tree<E, C>::avl_pred_iterator::operator--()
        {
            this->current_node = this->current_node->get_height() > 0
                                         ? this->successor(this->current_node)
                                         : this->current_node->get_parent()->minimum();

            return *this;
        }

        template <typename E, typename C>
        const typename avl_tree<E, C>::avl_pred_iterator avl_tree<E, C>::avl_pred_iterator::
                operator--(int)
        {
            avl_tree<E, C>::avl_pred_iterator result = *this;

            --(*this);

            return result;
        }

#pragma endregion
    }
}

#endif
