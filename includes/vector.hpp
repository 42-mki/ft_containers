#ifndef VECTOR_HPP
#define VECTOR_HPP

// for std::allocator
#include <memory>
// for u_nullptr
#include "../utils/utils.hpp"


namespace ft
{
    template <class T, class Alloc = std::allocator<T> >
    class vector
    {
    /*
    **  Member types
    */
    public:
        typedef T                                               value_type;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference                 const_reference;
        typedef typename allocator_type::pointer	                        pointer;
        typedef typename allocator_type::const_pointer	                const_pointer;
        // typedef iterator
        // typedef const_iterator
        // typedef reverse_iterator
        // typedef const_reverse_iterator
        // typedef difference_type
        typedef typename allocator_type::size_type              size_type;
    /*
    **  Private Member Variable
    */
    private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _end;
        pointer         _end_capacity;
    /*
    **  Private Member Function
    */
    private:
        void checkRange(const size_type& n) const
        {
            if (n >= this->size())
                throw (std::out_of_range("vector::checkRange: n (which is "
                        + ft::to_string(n) + ") >= this->size() (which is "
                        + ft::to_string(this->size()) + ")"));
        }
    /*
    **  Member Function
    **  orthodox canonical form
    */
    public:
        // 생성자
        // vector<int> v();
        vector  (const allocator_type& alloc = allocator_type())
        :
            _alloc(alloc),
            _start(u_nullptr),
            _end(u_nullptr),
            _end_capacity(u_nullptr)
        {}
        // 생성자
        // vector<int> v(10);
        // vector<int> v(10, 1);
        vector  (size_type n,
                const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
        :
            _alloc(alloc),
            _start(u_nullptr),
            _end(u_nullptr),
            _end_capacity(u_nullptr)
        {
            _start = _alloc.allocate(n);
            _end_capacity = _start + n;
            _end = _start;
            while (n--)
            {
                _alloc.construct(_end, val);
                _end++;
            }
        }
        vector(const vector &v);
        vector &operator=(const vector &v);
        ~vector() {}
    /*
    **  Iterators    
    */
    // public:
    //     begin();
    //     end();
    //     rbegin();
    //     rend();
    /*
    **  Capacity
    */
    // public:
    //     size();
    //     max_size();
    //     resize();
    //     capacity();
    //     empty();
    //     reserve();
    /*
    **  Element access:
    */
    public:
        reference operator[] (size_type n) { return (*(_start + n)); }
        const_reference operator[] (size_type n) { return (*(_start + n)); }
    //     at();
    //     front();
    //     back();
    /*
    **  Modifiers:
    */
    // public:
    //     assign();
    //     push_back();
    //     pop_back();
    //     insert();
    //     erase();
    //     swap();
    //     clear();
    /*
    **  Allocator
    */
    // public:
    //     get_allocator();
    /*
    **  Non-member function overloads
    */
    // template <class T, class Alloc>
    // bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {
        
    // }
    // template <class T, class Alloc>
    // bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {

    // }
    // template <class T, class Alloc>
    // bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {

    // }
    // template <class T, class Alloc>
    // bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {

    // }
    // template <class T, class Alloc>
    // bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {

    // }
    // template <class T, class Alloc>
    // bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    // {

    // }
    /*
    **  Non-member function overloads
    */
    // template <class T, class Alloc>
    // void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    // {

    };
}

#endif
