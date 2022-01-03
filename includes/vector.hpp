#ifndef VECTOR_HPP
#define VECTOR_HPP

// for std::allocator
#include <memory>
// for u_nullptr
#include "../utils/utils.hpp"


namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
    /*
    **  Member types
    */
    public:
        typedef T                                               value_type;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer	            pointer;
        typedef typename allocator_type::const_pointer	        const_pointer;
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
        allocator_type  _alloc_;
        pointer         _begin_;
        pointer         _end_;
        pointer         _end_cap_;
    /*
    **  Private Member Function
    */
    private:
        void checkRange(const size_type& n) const
        {
            if (n >= this->size())
                throw (std::out_of_range("vector"));
        }
    /*
    **  Member Function
    **  orthodox canonical form
    */
    public:
        vector  (const allocator_type& alloc = allocator_type())
        :
            _alloc_(alloc),
            _begin_(u_nullptr),
            _end_(u_nullptr),
            _end_cap_(u_nullptr)
        {}
        vector  (size_type _n,
                const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type())
        :
            _alloc_(alloc),
            _begin_(u_nullptr),
            _end_(u_nullptr),
            _end_cap_(u_nullptr)
        {
            _begin_ = _alloc_.allocate(_n);
            _end_cap_ = _begin_ + _n;
            _end_ = _begin_;
            while (_n--)
            {
                _alloc_.construct(_end_, val);
                _end_++;
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
    public:
        size_type size(void) const
        {
            return (this->_end_ - this->_begin_);
        }
        size_type max_size(void) const
        {
            return allocator_type().max_size();
        }
    //     resize();
        size_type capacity(void) const
        {
            return (this->_end_cap_ - this->_begin_);
        }
        bool empty() const
        {
            return this->_begin_ == this->_end_;
        }
        void reserve(size_type n)
        {
            if (n > this->max_size())
                throw (std::length_error("vector::reserve"));
            else if (n > this->capacity())
            {
                pointer prev_begin = _begin_;
                pointer prev_end = _end_;
                size_type prev_size = this->size();
                size_type prev_capacity = this->capacity();

                _begin_ = _alloc_.allocate(n);
                _end_cap_ = _begin_ + n;
                _end_ = _begin_;
                while (prev_begin != prev_end)
                {
                    _alloc_.construct(_end_, *prev_begin);
                    _end_++;
                    prev_begin++;
                }
                _alloc_.deallocate(prev_begin - prev_size, prev_capacity);
            }
        }
    /*
    **  Element access:
    */
    public:
        reference operator[] (size_type _n)
        {
            return this->_begin_[_n];
        }
        const_reference operator[] (size_type _n) const
        {
            return this->_begin_[_n];
        }
        reference at (size_type _n)
        {
            checkRange(_n);
            return this->_begin_[_n];
        }
        const_reference at (size_type _n) const
        {
            checkRange(_n);
            return this->_begin_[_n];
        }
        reference front()
        {
            return *this->_begin_;
        }
        const reference front() const
        {
            return *this->_begin_;
        }
        reference back()
        {
            return *(this->_end_ - 1);
        }
        const reference back() const
        {
            return *(this->_end_ - 1);
        }
    /*
    **  Modifiers:
    */
    // public:
        // assign();
        void push_back (const value_type& val)
        {
            if (_end_ == _end_cap_)
            {
                int next_capacity = (this->size() > 0) ? (int)(this->size() * 2) : 1;
                this->reserve(next_capacity);
            }
            _alloc_.construct(_end_, val);
            _end_++;
        }
        void pop_back()
        {
            _alloc_.destroy(&this->back());
            _end_--;
        }
        // insert();
        // erase();
        void swap(vector &x)
        {
            // if (x == this)
            //     return ;
            
            pointer temp_begin = x._begin_;
            pointer temp_end = x._end_;
            pointer temp_end_cap = x._end_cap_;
            allocator_type temp_alloc = x._alloc_;

            x._begin_ = this->_begin_;
            x._end_ = this->_end_;
            x._end_cap_ = this->_end_cap_;
            x._alloc_ = this->_alloc_;

            this->_begin_ = temp_begin;
            this->_end_ = temp_end;
            this->_end_cap_ = temp_end_cap;
            this->_alloc_ = temp_alloc;
        }
        void clear()
        {
            size_type temp_size = this->size();
            for (size_type i = 0; i < temp_size; i++)
            {
                _end_--;
                _alloc_.destroy(_end_);
            }
        }
    /*
    **  Allocator
    */
    public:
        allocator_type get_allocator(void)
        {
            return _alloc_;
        }
    };
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
    template <class T, class Alloc>
    void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
    {
        x.swap(y);
    };
}

#endif
