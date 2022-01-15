#ifndef MAP_HPP
# define MAP_HPP
# include <map>

// #include "BinarySearchTree.hpp"

namespace ft
{
    template <
        class Key,
        class T,
        class Compare = ft::less<Key>,
        class Alloc = std::allocator<ft::pair<const Key, T> >
    >
    class map
    {
        public:
            typedef Key                                     key_type;
            typedef T                                       mapped_type;
            typedef ft::pair<const key_type, mapped_type>   value_type;
            typedef size_t                                  size_type;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef Compare                                 key_compare;
            typedef Alloc                                           allocator_type;
            typedef typename allocator_type::reference              reference
            typedef typename allocator_type::const_reference        const_reference
            typedef typename allocator_type::pointer                pointer;
            typedef typename allocator_type::const_pointer          const_pointer;
            typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator          iterator;
            typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator    const_iterator;
            typedef typename ft::reverse_iterator<iterator>         reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;

        public:
            class value_compare : ft::binary_function<>
            {
                typedef 
            }

        private:
            allocator_type                          _alloc
            Compare                                 _comp;
            Binary_search_tree<value_type, Compare> _bst;

        public:
            // Constructor
            explicit map ()
            :
            {}

            template <class InputIterator>
            map ()
            :
            {}
            map ()
            :
            {}
            map& operator= ()
            {

            }
            virtual map()
            {

            }
            allocator_type get_allocator()
            {

            }
            // Element access
            at()
            {

            }
            mapped_type &operator[] ()
            {

            }
            // Iterators
            iterator begin()
            {

            }
            const_iterator begin()
            {

            }
            iterator end()
            {

            }
            const_iterator end() const
            {

            }
            reverse_iterator rbegin()
            {

            }
            const_reverse_iterator rbegin() const
            {

            }
            reverse_iterator rend()
            {

            }
            const_reverse_iterator rend() const
            {

            }
            // Capacity
            empty()
            {

            }
            size_type size() const
            {

            }
            size_type max_size() const
            {

            }
            // Modifiers
            void clear()
            {

            }
            pair<iterator, bool> insert (const value_type &val)
            {

            }
            iterator insert (iterator position, const value_type& val)
            {

            }
            template <class InputIterator>
            void insert ()
            {

            }
            void erase (iterator position)
            {

            }
            size_type erase (const key_type& k)
            {

            }
            void erase (iterator first, iterator last)
            {

            }
            void swap (map& x)
            {

            }
            // Lookup
            size_type count (const key_type& k) const
            {

            }
            iterator find (const key_type& k)
            {

            }
            const_iterator find (const key_type& k) const
            {

            }
            ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
            {

            }
            ft::pair<iterator, iterator> equeal_range (const key_type& k)
            {

            }
            iterator lower_bound (const key_type& k)
            {

            }
            const_iterator lower_bound (const key_type& k) const
            {

            }
            iterator upper_bound (const key_type& k)
            {

            }
            const_iterator upper_bound (const key_type& k) const
            {

            }

            // Observers
            key_compare key_comp() const
            {

            }
            value_compare value_comp() const
            {

            }
    };
}

#endif
