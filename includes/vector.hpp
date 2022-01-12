#ifndef VECTOR_HPP
#define VECTOR_HPP

// for std::allocator
#include <memory>
// for u_nullptr
#include "../utils/Utils.hpp"

namespace ft
{
    template <typename T, typename Alloc = std::allocator<T> >
    class vector
    {
    /*
    **  Member types
    */
    public:
        typedef T                                                       value_type;
        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer	                    pointer;
        typedef typename allocator_type::const_pointer	                const_pointer;
        typedef ft::random_access_iterator<value_type>                  iterator;
        typedef ft::random_access_iterator<const value_type>            const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
        typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type                      size_type;
    /*
    **  Private Member Variable
    */
    private:
        allocator_type  m_alloc;
        pointer         m_begin;
        pointer         m_end;
        pointer         m_end_cap;
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
        vector  (const allocator_type& _alloc = allocator_type())
        :
            m_alloc(_alloc),
            m_begin(u_nullptr),
            m_end(u_nullptr),
            m_end_cap(u_nullptr)
        {}
        vector  (size_type _n,
                const value_type& val = value_type(),
                const allocator_type& _alloc = allocator_type())
        :
            m_alloc(_alloc),
            m_begin(u_nullptr),
            m_end(u_nullptr),
            m_end_cap(u_nullptr)
        {
            m_begin = m_alloc.allocate(_n);
            m_end_cap = m_begin + _n;
            m_end = m_begin;
            while (_n--)
            {
                m_alloc.construct(m_end, val);
                m_end++;
            }
        }
        vector(const vector &v)
        :
            m_alloc(v.m_alloc),
            m_begin(u_nullptr),
            m_end(u_nullptr),
            m_end_cap(u_nullptr)
        {
            this->insert(this->begin(), v.begin(), v.end());
        }
        vector &operator=(const vector &v)
        {
            if (v == *this)
                return (*this);
            this->clear();
            this->insert(this->end(), v.begin(), v.end());
            return (*this);
        }
        ~vector()
        {
            this->clear();
            m_alloc.deallocate(m_begin, this->capacity());
        }
    /*
    **  Iterators    
    */
    public:
        iterator begin()
        {
            return (m_begin);
        }
        const_iterator begin() const
        {
            return (m_begin);
        }
        iterator end()
        {
            if (this->empty())
                return (this->begin());
            return (m_end);
        }
        const_iterator end() const
        {
            if (this->empty())
                return (this->begin());
            return (m_end);
        }
        reverse_iterator rbegin()
        {
            return reverse_iterator(this->end());
        }
        const_reverse_iterator rbegin() const
        {
            return reverse_iterator(this->end());
        }
        reverse_iterator rend()
        {
            return reverse_iterator(this->begin());
        }
        const_reverse_iterator rend() const
        {
            return reverse_iterator(this->begin());
        }
    /*
    **  Capacity
    */
    public:
        size_type size(void) const
        {
            return (this->m_end - this->m_begin);
        }
        size_type max_size(void) const
        {
            return allocator_type().max_size();
        }
        void resize (size_type n, value_type val = value_type())
        {
            if (n > this->max_size())
                throw (std::length_error("vector::resize"));
            else if (n < this->size())
            {
                while (this->size() > n)
                {
                    --m_end;
                    m_alloc.destroy(m_end);
                }
            }
            else
                this->insert(this->end(), n - this->size(), val);
        }
        size_type capacity(void) const
        {
            return (this->m_end_cap - this->m_begin);
        }

        bool empty() const
        {
            return this->m_begin == this->m_end;
        }

        void reserve(size_type n)
        {
            if (n > this->max_size())
                throw (std::length_error("vector::reserve"));
            else if (n > this->capacity())
            {
                pointer temp_begin = m_begin;
                pointer temp_end = m_end;
                size_type temp_size = this->size();
                size_type temp_capacity = this->capacity();

                m_begin = m_alloc.allocate(n);
                m_end_cap = m_begin + n;
                m_end = m_begin;
                while (temp_begin != temp_end)
                {
                    m_alloc.construct(m_end, *temp_begin);
                    m_end++;
                    temp_begin++;
                }
                m_alloc.deallocate(temp_begin - temp_size, temp_capacity);
            }
        }
    /*
    **  Element access:
    */
    public:
        reference operator[] (size_type _n)
        {
            return this->m_begin[_n];
        }
        const_reference operator[] (size_type _n) const
        {
            return this->m_begin[_n];
        }
        reference at (size_type _n)
        {
            checkRange(_n);
            return this->m_begin[_n];
        }
        const_reference at (size_type _n) const
        {
            checkRange(_n);
            return this->m_begin[_n];
        }
        reference front()
        {
            return *this->m_begin;
        }
        const reference front() const
        {
            return *this->m_begin;
        }
        reference back()
        {
            return *(this->m_end - 1);
        }
        const reference back() const
        {
            return *(this->m_end - 1);
        }
    /*
    **  Modifiers:
    */
    public:
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
        typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
        {
            if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
                throw (ft::InvalidIteratorException<void>());
            // assign은 기존 elements를 초기화한다.
            this->clear();
            size_type dist = ft::distance(first, last);
            if (m_end_cap - m_begin >= dist)
            {
                while (&(*first) != &(*last))
                {
                    m_alloc.construct(m_end, *first);
                    first++;
                    last++;
                }
            }
            else
            {
                pointer temp_begin = m_alloc.allocate(dist);
                pointer temp_end = temp_begin;
                pointer temp_end_cap = temp_begin + dist;

                while (&(*first) != &(*last))
                {
                    m_alloc.construct(m_end, *first);
                    first++;
                    last++;
                }

                m_alloc.deallocate(m_begin, this->capacity());
                m_begin = temp_begin;
                m_end = temp_end;
                m_end_cap = temp_end_cap;
            }
        }

        void assign (size_type n, const value_type& val)
        {
            this->clear();
            if (n == 0)
                return ;
            if (size_type(m_end_cap - m_begin) >= n)
            {
                while (n)
                {
                    m_alloc.construct(m_end++, val);
                    n--;
                }
            }
            else
            {
                m_alloc.deallocate(m_begin, this->capacity());
                m_begin = m_alloc.allocate(n);
                m_end = m_begin;
                m_end_cap = m_begin + n;
                while (n)
                {
                    m_alloc.construct(m_end++, val);
                    n--;
                }
            }
        }
        void push_back(const value_type& val)
        {
            if (m_end == m_end_cap)
            {
                int next_capacity = (this->size() > 0) ? (int)(this->capacity() * 2) : 1;
                this->reserve(next_capacity);
            }
            m_alloc.construct(m_end, val);
            m_end++;
        }
        void pop_back()
        {
            m_alloc.destroy(&this->back());
            m_end--;
        }

        // insert()
        iterator insert (iterator position, const value_type& val)
        {
            size_type pos_len = &(*position) - m_begin;
            // vector가 꽉 차있지 않다면
            if (size_type(m_end_cap - m_end) >= 1)
            {
                for (size_type i = 0; i < pos_len; i++)
                    m_alloc.construct(m_end - i, *(m_end - i - 1));
                m_end++;
                m_alloc.construct(&(*position), val);
            }
            else
            {
                int next_cap = (this->capacity() * 2 > 0) ? this->capacity() * 2 : 1;
                pointer temp_begin = m_alloc.allocate(next_cap);
                pointer temp_end = temp_begin + this->size() + 1;
                pointer temp_end_cap = temp_begin + next_cap;

                for (size_type i = 0; i < pos_len; i++)
                    m_alloc.construct(temp_begin + i, *(m_begin + i));
                m_alloc.construct(temp_begin + pos_len, val);
                for (size_type j = 0; j < this->size() - pos_len; j++)
                    m_alloc.construct(temp_end - j - 1, *(m_end - j - 1));
                
                for (size_type l = 0; l < this->size(); l++)
                    m_alloc.destroy(m_begin + l);
                if (m_begin)
                    m_alloc.deallocate(m_begin, this->capacity());
                m_begin = temp_begin;
                m_end = temp_end;
                m_end_cap = temp_end_cap;
            }
            return (iterator(m_begin + pos_len));
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            if (n == 0)
                return ;
            if (n > this->max_size())
                throw (std::length_error("vector::insert (fill)"));
            size_type pos_len = &(*position) - m_begin;
            // insert할 val의 갯수 n이 vector의 빈 공간보다 적다면, 즉 충분하다면
            if (size_type(m_end_cap - m_end) >= n)
            {
                for (size_type i = 0; i < this->size() - pos_len; i++)
                    m_alloc.construct(m_end - i + (n - 1), *(m_end - i - 1));
                m_end += n;
                while (n)
                {
                    m_alloc.construct(&(*position) + (n - 1), val);
                    n--;
                }
            }
            // 공간이 부족하다면
            else
            {
                // 현재 vector capacity를 두배로 늘린다.
                int next_cap = (this->capacity() > 0) ? (int)(this->capacity() * 2) : 1;
                pointer temp_begin = m_alloc.allocate(next_cap);
                pointer temp_end_cap = temp_begin + next_cap;
                pointer temp_end;
                // 그래도 n이 너무 커서 두배로 capacity를 늘려도 부족하다면
                if (size_type(temp_end_cap - temp_begin) < this->size() + n)
                {
                    // 할당된 공간을 해제하고 새로 할당
                    if (temp_begin)
                        m_alloc.deallocate(temp_begin, temp_end_cap - temp_begin);
                    next_cap = this->size() + n;
                    temp_begin = m_alloc.allocate(next_cap);
                    temp_end = temp_begin + this->size() + n;
                    temp_end_cap = temp_begin + next_cap;
                }
                temp_end = temp_begin + this->size() + n;

                // 새로 insert할 iter 전까지 기존 elements 복사
                for (int i = 0; i < (&(*position) - m_begin); i++)
                    m_alloc.construct(temp_begin + i, *(m_begin + i));
                // 새로운 elements 추가
                for (size_type k = 0; k < n; k++)
                    m_alloc.construct(temp_begin + pos_len + k, val);
                // 이후 남은 vector element 복사
                for (size_type j = 0; j < (this->size() - pos_len); j++)
                    m_alloc.construct(temp_end - j - 1, *(m_end - j - 1));
                // 기존 vector destroy
                for (size_type u = 0; u < this->size(); u++)
                    m_alloc.destroy(m_begin + u);
                m_alloc.deallocate(m_begin, this->capacity());

                m_begin = temp_begin;
                m_end = temp_end;
                m_end_cap = temp_end_cap;
            }
        }

        // insert range
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
        {
            if (!ft::is_ft_iterator_tagged<typename ft::iterator_traits<InputIterator>::iterator_category>::value)
                throw (ft::InvalidIteratorException<void>());
            size_type dist = ft::distance(first, last);
            size_type pos_len = &(*position) - m_begin;
            // vector의 남은 공간이 넉넉하다면
            if (size_type(m_end_cap - m_end) >= dist)
            {
                // insert할 position 이후 element들을 dist만큼 뒤로 미루기
                for (size_type i = 0; i < this->size() - pos_len; i++)
                    m_alloc.construct(m_end - i + (dist - 1), *(m_end - i - 1));
                m_end += dist;
                // 그리고 그 사이에 새로운 element채우기
                while (&(*first) != &(*last))
                {
                    m_alloc.construct(&(*position), *first);
                    position++;
                    first++;
                }
            }
            // 넉넉하지 않다면
            else
            {
                pointer temp_begin = m_alloc.allocate(this->capacity() * 2);
                pointer temp_end = temp_begin + this->size() + dist;
                pointer temp_end_cap = temp_begin + (this->capacity() * 2);
                // 그래도 n이 너무 커서 두배로 capacity를 늘려도 부족하다면
                if (size_type(temp_end_cap - temp_begin) < this->size() + dist)
                {
                    // 할당된 공간을 해제하고 새로 할당
                    if (temp_begin)
                        m_alloc.deallocate(temp_begin, temp_end_cap - temp_begin);
                    temp_begin = m_alloc.allocate(this->size() + dist);
                    temp_end = temp_begin + this->size() + dist;
                    temp_end_cap = temp_end;
                }

                // 새로 insert할 iter 전까지 기존 elements 복사
                for (size_type i = 0; i < pos_len; i++)
                    m_alloc.construct(temp_begin + i, *(m_begin + i));
                // 새로운 elements 추가
                for (int j = 0; &(*first) != &(*last); first++, j++)
                    m_alloc.construct(temp_begin + pos_len + j, *first);
                // 이후 남은 vector element 복사
                for (size_type k = 0; k < this->size() - pos_len; k++)
                    m_alloc.construct(temp_begin + pos_len + dist + k, *(m_begin + pos_len + k));
                
                // 기존 vector destroy
                for (size_type u = 0; u < this->size(); u++)
                    m_alloc.destroy(m_begin + u);
                m_alloc.deallocate(m_begin, this->capacity());

                m_begin = temp_begin;
                m_end = temp_end;
                m_end_cap = temp_end_cap;
            }
        }

        iterator erase(iterator position)
        {
            pointer p_pos = &(*position);
            m_alloc.destroy(&(*position));
            if (&(*position) + 1 == m_end)
                m_alloc.destroy(&(*position));
            else
            {
                for (int i = 0; i < m_end - &(*position) - 1; i++)
                {
                    m_alloc.construct(&(*position) + i, *(&(*position) + i + 1));
                    m_alloc.destroy(&(*position) + i + 1);
                }
            }
            m_end -= 1;
            return (iterator(p_pos));
        }

        iterator erase (iterator first, iterator last)
        {
            pointer p_first = &(*first);
            for (; &(*first) != &(*last); first++)
                m_alloc.destroy(&(*first));
            for (int i = 0; i < m_end - &(*last); i++)
            {
                m_alloc.construct(p_first + i, *(&(*last)) + i);
                m_alloc.destroy(&(*last));
            }
            m_end -= (&(*last) - p_first);
            return (iterator(p_first));
        }

        void swap(vector &x)
        {
            pointer temp_begin = x.m_begin;
            pointer temp_end = x.m_end;
            pointer temp_endcap = x.m_end_cap;
            allocator_type temp_alloc = x.m_alloc;

            x.m_begin = this->m_begin;
            x.m_end = this->m_end;
            x.m_end_cap = this->m_end_cap;
            x.m_alloc = this->m_alloc;

            this->m_begin = temp_begin;
            this->m_end = temp_end;
            this->m_end_cap = temp_endcap;
            this->m_alloc = temp_alloc;
        }
        
        void clear()
        {
            size_type tempsize = this->size();
            for (size_type i = 0; i < tempsize; i++)
            {
                m_end--;
                m_alloc.destroy(m_end);
            }
        }
    /*
    **  Allocator
    */
    public:
        allocator_type get_allocator(void)
        {
            return m_alloc;
        }
    };
    /*
    **  Non-member function overloads
    */
    template <class T, class Alloc>
    bool operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return (false);
        typename ft::vector<T>::const_iterator first1 = lhs.begin();
        typename ft::vector<T>::const_iterator first2 = rhs.begin();
        while (first1 != lhs.end())
        {
            if (first2 == rhs.end() || *first1 != *first2)
                return (false);
            ++first1;
            ++first2;
        }
        return (true);
    }
    template <class T, class Alloc>
    bool operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        return (!(lhs == rhs));
    }
    template <class T, class Alloc>
    bool operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }
    template <class T, class Alloc>
    bool operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        return (!(rhs < lhs));
    }
    template <class T, class Alloc>
    bool operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        return (rhs < lhs);
    }
    template <class T, class Alloc>
    bool operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
    {
        return (!(lhs < rhs));
    }
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
