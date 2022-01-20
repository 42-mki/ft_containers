#ifndef MAP_HPP
# define MAP_HPP
# include "BST.hpp"

namespace ft
{
    // https://www.cplusplus.com/reference/map/map/
    template <  class Key,
                class T,
                class Compare = ft::less<Key>,
                class Alloc = std::allocator<ft::pair<const Key, T> >
                >
    class map
    {
        public:
            typedef Key                                                         key_type;
            typedef T                                                           mapped_type;
            typedef ft::pair<key_type, mapped_type>                             value_type;
            typedef Compare                                                     key_compare;
            typedef Alloc                                                       allocator_type;
            // https://www.cplusplus.com/reference/map/map/value_comp/
            // while ( mymap.value_comp()(*it++, highest) )
            class value_compare : public ft::binary_function<value_type, value_type, bool>
            {
                friend class map<key_type, mapped_type, key_compare, allocator_type>;

                protected:
                    Compare comp;
                    value_compare   (Compare c) : comp(c) {}
                public:
                    bool operator() (const value_type& x, const value_type& y) const
                    {
                        return comp(x.first, y.first);
                    }
            };
            typedef typename allocator_type::reference                          reference;
            typedef typename allocator_type::const_reference                    const_reference;
            typedef typename allocator_type::pointer                            pointer;
            typedef typename allocator_type::const_pointer                      const_pointer;
            typedef typename ft::BST<value_type, key_compare>::iterator         iterator;
            typedef typename ft::BST<value_type, key_compare>::const_iterator   const_iterator;
            typedef typename ft::reverse_iterator<iterator>                     reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator>               const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type     difference_type;
            typedef size_t                                                      size_type;

        private:
            allocator_type                          _alloc;
            Compare                                 _comp;
            BST<value_type, Compare>                _bst;

        public:
            // Constructor
            // https://www.cplusplus.com/reference/map/map/map/
            explicit map (  const key_compare& comp = key_compare(),
                            const allocator_type& alloc = allocator_type())
            :
                _alloc(alloc),
                _comp(comp),
                _bst()
            {}
            template <class InputIterator>
            map (   InputIterator first, InputIterator last,
                    const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            :
                _alloc(alloc),
                _comp(comp),
                _bst()
            {
                if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
                    throw (ft::invalid_iterator_exception<void>());
                this->insert(first, last);
            }
            map (const map& x)
            :
                _alloc(x._alloc),
                _comp(x._comp),
                _bst()
            {
                this->insert(x.begin(), x.end());
            }
            // https://www.cplusplus.com/reference/map/map/operator=/
            map& operator= (const map& x)
            {
                this->clear();
                this->insert(x.begin(), x.end());
                return *this;
            }
            // https://www.cplusplus.com/reference/map/map/~map/
            virtual ~map()
            {
                this->clear();
            }
            // https://www.cplusplus.com/reference/map/map/get_allocator/
            allocator_type get_allocator() const { return _alloc; }
            // Element access
            mapped_type &operator[] (const key_type& k)
            {
                iterator tmp = this->find(k);

                if (tmp == this->end())
                    this->insert(ft::make_pair(k, mapped_type()));
                tmp = this->find(k);
                return ((*tmp).second);
            }
            // Iterators
            // https://www.cplusplus.com/reference/map/map/begin/
            iterator begin() { return iterator(_bst._last_node->left, _bst._last_node); }
            const_iterator begin() const { return const_iterator(_bst._last_node->left, _bst._last_node); }
            // https://www.cplusplus.com/reference/map/map/end/
            iterator end() { return iterator(_bst._last_node, _bst._last_node); }
            const_iterator end() const { return const_iterator(_bst._last_node, _bst._last_node); }
            // https://www.cplusplus.com/reference/map/map/rbegin/
            reverse_iterator rbegin() { return reverse_iterator(this->end()); }
            const_reverse_iterator rbegin() const { return reverse_iterator(this->end()); }
            // https://www.cplusplus.com/reference/map/map/rend/
            reverse_iterator rend() { return reverse_iterator(this->begin()); }
            const_reverse_iterator rend() const { return reverse_iterator(this->begin()); }
            // Capacity
            //https://www.cplusplus.com/reference/map/map/empty/
            bool empty() const { return _bst._last_node->parent == _bst._last_node; }
            // https://www.cplusplus.com/reference/map/map/size/
            size_type size() const { return _bst.getSize(); }
            size_type max_size() const { return _bst.max_size(); }
            // // Modifiers
            void clear()
            {
                this->erase(this->begin(), this->end());
            }
            // https://www.cplusplus.com/reference/map/map/insert/
            pair<iterator, bool> insert (const value_type &val)
            {
                return _bst.insertPair(val);
            }
            iterator insert (iterator position, const value_type& val)
            {
                (void)position;
                return _bst.insertPair(val).first;

            }
            template <class InputIterator>
            void insert (InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
            {
                if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
                    throw (ft::invalid_iterator_exception<void>());
                difference_type n = ft::distance(first, last);
                while (n--)
                    this->insert(*(first++));
            }
            size_type erase (const key_type& k)
            {
                if (this->find(k) == this->end())
                    return 0;
                _bst.removeByKey(ft::make_pair(k, mapped_type()));
                return 1;
            }
            void erase (iterator position)
            {
                this->erase((*position).first);
            }
            void erase (iterator first, iterator last)
            {
                while (first != last)
                    this->erase((*(first++)).first);
            }
            void swap (map& x)
            {
                _bst.swap(x._bst);
            }
            // Lookup
            // https://www.cplusplus.com/reference/map/map/count/
            // k값이 있다면 1 없다면 0
            size_type count (const key_type& k) const
            {
                const_iterator begin = this->begin();
                const_iterator end = this->end();

                while (begin != end)
                {
                    if ((*begin).first == k)
                        return (1);
                    begin++;
                }
                return (0);
            }
            // https://www.cplusplus.com/reference/map/map/find/
            // k값을 가진 key가 map에 있다면, 해당 iterator를 반환
            iterator find (const key_type& k)
            {
                return iterator(_bst.serachByKey(ft::make_pair(k, mapped_type())), _bst._last_node);
            }
            const_iterator find (const key_type& k) const
            {
                return const_iterator(_bst.serachByKey(ft::make_pair(k, mapped_type())), _bst._last_node);
            }
            // https://www.cplusplus.com/reference/map/map/lower_bound/
            // k보다 크거나 같은 값중 가장 작은 값의 it를 return
            iterator lower_bound (const key_type& k)
            {
                iterator begin = this->begin();
                iterator end = this->end();

                while (begin != end)
                {
                    if (_comp((*begin).first, k) == false)
                        break;
                    begin++;
                }
                return begin;   
            }
            const_iterator lower_bound (const key_type& k) const
            {
                return (const_iterator(this->lower_bound(k)));
            }
            iterator upper_bound (const key_type& k)
            {
                iterator begin = this->begin();
                iterator end = this->end();

                while (begin != end)
                {
                    if (_comp(k, (*begin).first))
                        break;
                    begin++;
                }
                return begin;
            }
            const_iterator upper_bound (const key_type& k) const
            {
                return (const_iterator(this->upper_bound(k)));
            }
            // https://www.cplusplus.com/reference/map/map/equal_range/
            ft::pair<const_iterator, const_iterator> equal_range (const key_type& k) const
            {
                return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
            }
            ft::pair<iterator, iterator> equal_range (const key_type& k)
            {
                return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
            }
            // Observers
            // https://www.cplusplus.com/reference/map/map/key_comp/
            key_compare key_comp() const
            {
                return key_compare();
            }
            // https://www.cplusplus.com/reference/map/map/value_comp/
            value_compare value_comp() const
            {
                return value_compare(key_compare());
            }
    };
}

#endif
