#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "Utils.hpp"
# include <stddef.h>

namespace ft
{   
    // iterator tags
    // https://en.cppreference.com/w/cpp/iterator/iterator_tags
    class input_iterator_tag { };
    class output_iterator_tag { };
    class forward_iterator_tag : public input_iterator_tag { };
    class bidirectional_iterator_tag : public forward_iterator_tag { };
    class random_access_iterator_tag : public bidirectional_iterator_tag { };

    // output이면 false 그 외에는 true
    template <bool is_valid, typename T>
    struct valid_iterator_tag_res
    {
        typedef T type;
        static const bool value = is_valid;
    };

    // defalut
    template <typename T>
    struct is_input_iterator_tagged
        : public valid_iterator_tag_res<false, T> {};
    // template specialization
    template <>
    struct is_input_iterator_tagged<ft::input_iterator_tag>
        : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::forward_iterator_tag>
        : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
        : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::random_access_iterator_tag>
        : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

    // ft_iterator이면 true
    // default
    template <typename T>
    struct is_ft_iterator_tagged
        : public valid_iterator_tag_res<false, T> {};
    template <>
    struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
        : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};
    template <>
    struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
        : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};
    template <>
    struct is_ft_iterator_tagged<ft::forward_iterator_tag>
        : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};
    template <>
    struct is_ft_iterator_tagged<ft::output_iterator_tag>
        : public valid_iterator_tag_res<true, ft::output_iterator_tag> {};
    template <>
    struct is_ft_iterator_tagged<ft::input_iterator_tag>
        : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

    // exception
    template <typename T>
    class invalid_iterator_exception : public std::exception
    {
    public:
        virtual const char * what() const throw()
        {
            return "Is invalid iterator tag : ";
        }
    };
    
    // iterator_traits
    // https://en.cppreference.com/w/cpp/iterator/iterator_traits
    template<class Iter>
    struct iterator_traits
    {
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
        typedef typename Iter::iterator_category    iterator_category;
    };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef std::ptrdiff_t                      difference_type;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef ft::random_access_iterator_tag      iterator_category;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef std::ptrdiff_t                      difference_type;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;
        typedef ft::random_access_iterator_tag      iterator_category;
    };
    
    // std::distance
    // https://en.cppreference.com/w/cpp/iterator/distance
    template<class InputIt>
    typename ft::iterator_traits<InputIt>::difference_type
    distance (InputIt first, InputIt last)
    {
        typename ft::iterator_traits<InputIt>::difference_type ret = 0;
        while (first != last)
        {
            first++;
            ret++;
        }
        return ret;
    }

    // base iterator
    // https://en.cppreference.com/w/cpp/iterator/iterator
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
    public:
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };

    // bidirectional_iterator
    // 왜 상속받은 것을 또 하고 있지?
    // 왜 private이지?
    // 왜 다 만들다 만것 같지?

    template <class T>
    class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type        value_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
        typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference         reference;
    private:
        pointer _elem;
    };

    // reverse_iterator
    template <class Iterator>
    class reverse_iterator
    {

        public:
            typedef Iterator    iterator_type;
            typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
            typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
            typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
            typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
            typedef typename ft::iterator_traits<Iterator>::reference           reference;

            reverse_iterator()
            :
                _elem()
            {}
            
            explicit reverse_iterator (iterator_type it)
            :
                _elem(it)
            {}

            template <class Iter>
            reverse_iterator (const reverse_iterator<Iter>& rev_iter)
            :
                _elem(rev_iter.base())
            {}

            virtual ~reverse_iterator() {}

            iterator_type base() const
            {
                return _elem;
            }

            reference operator *() const
            {
                iterator_type temp = _elem;
                return (*(--temp));
            }

            reverse_iterator operator+ (difference_type n) const
            {
                return reverse_iterator(_elem - n);
            }

            reverse_iterator& operator++()
            {
                --_elem;
                return (*this);
            }

            reverse_iterator operator++(int)
            {
                reverse_iterator temp = *this;
                ++(*this);
                return (temp);
            }

            reverse_iterator& operator+= (difference_type n)
            {
                _elem -= n;
                return (*this);
            }

            reverse_iterator operator- (difference_type n) const
            {
                return reverse_iterator(_elem + n);
            }

            reverse_iterator& operator--()
            {
                ++_elem;
                return (*this);
            }

            reverse_iterator operator--(int)
            {
                reverse_iterator temp = *this;
                --(*this);
                return (temp);
            }

            reverse_iterator& operator-= (difference_type n)
            {
                _elem += n;
                return (*this);
            }
            
            pointer operator-> () const
            {
                return &(operator*());
            }

            reference operator[] (difference_type n) const
            {
                return (this->base()[-n - 1]);
            }
        private:
            iterator_type   _elem;
    };

    template <class Iterator>
    bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() != rhs.base());
    }
    template <class Iterator_L, class Iterator_R>
    bool operator != (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <class Iterator>
    bool operator < (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() > rhs.base());
    }
    template <class Iterator_L, class Iterator_R>
    bool operator < (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <class Iterator>
    bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }
    template <class Iterator_L, class Iterator_R>
    bool operator <= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <class Iterator>
    bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() < rhs.base());
    }
    template <class Iterator_L, class Iterator_R>
    bool operator > (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <class Iterator>
    bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    template <class Iterator_L, class Iterator_R>
    bool operator >= (const reverse_iterator<Iterator_L>& lhs, const reverse_iterator<Iterator_R>& rhs)
    {
        return (lhs.base() <= rhs.base());
    }
    
    // n + rev_it
    template <class Iterator>
    reverse_iterator<Iterator> operator+ (
        typename reverse_iterator<Iterator>::difference_type n,
        const reverse_iterator<Iterator>& rev_it
    )
    {
        return (rev_it + n);
    }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator- (
        const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs
    )
    {
        return (lhs.base() - rhs.base());
    }

    template <class Iterator_L, class Iterator_R>
    bool operator- (
        const reverse_iterator<Iterator_L>& lhs,
        const reverse_iterator<Iterator_R>& rhs
    )
    {
        return (lhs.base() - rhs.base());
    }

    // random_access_iterator
    template <typename T>
    class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
    {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type   difference_type;
            typedef T*  pointer;
            typedef T&  reference;

            random_access_iterator()
            :
                _elem(u_nullptr)
            {}

            random_access_iterator(pointer elem)
            :
                _elem(elem)
            {}

            random_access_iterator(const random_access_iterator& rand_iter)
            :
                _elem(rand_iter._elem)
            {}

            random_access_iterator &operator=(const random_access_iterator& rand_iter)
            {
                if (this == &rand_iter)
                    return (*this);
                this->_elem = rand_iter._elem;
                return (*this);
            }

            virtual ~random_access_iterator() {}

            pointer base() const
            {
                return (this->_elem);
            }

            reference operator*() const
            {
                return (*_elem);
            }

            pointer operator->()
            {
                return &(operator*());
            }

            random_access_iterator& operator++()
            {
                _elem++;
                return (*this);
            }

            random_access_iterator operator++(int)
            {
                random_access_iterator ret(*this);
                operator++();
                return (ret);
            }

            random_access_iterator& operator--()
            {
                _elem--;
                return (*this);
            }

            random_access_iterator operator--(int)
            {
                random_access_iterator ret(*this);
                operator--();
                return (ret);
            }

            random_access_iterator operator+(difference_type n) const
            {
                return (_elem + n);
            }
            
            random_access_iterator operator-(difference_type n) const
            {
                return (_elem - n);
            }
            
            random_access_iterator& operator+=(difference_type n)
            {
                _elem += n;
                return (*this);
            }

            random_access_iterator& operator-=(difference_type n)
            {
                _elem -= n;
                return (*this);
            }

            reference operator[] (difference_type n)
            {
                return (*(operator+(n)));
            }

            operator random_access_iterator<const T> () const
            {
                return (random_access_iterator<const T>(this->_elem));
            }
        private:
            pointer _elem;
    };

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator==(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator!=(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<=(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>=(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename T>
    ft::random_access_iterator<T>
    operator+ (
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rand_iter
    )
    {
        return (&(*rand_iter) + n);
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-(
        const ft::random_access_iterator<T> lhs,
        const ft::random_access_iterator<T> rhs
    )
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-(
        const ft::random_access_iterator<T_L> lhs,
        const ft::random_access_iterator<T_R> rhs
    )
    {
        return (lhs.base() - rhs.base());
    }
} // namespace ft

#endif