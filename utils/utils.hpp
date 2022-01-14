#ifndef UTILS_HPP
# define UTILS_HPP

#include <sstream>  // std::ostringstream

// nullptr
// NULL은 문제가 있어서 C++11에서 도입되었습니다
// https://www.amazon.com/dp/0201924889

const class
{
public:
    template <class T>
    operator T *() const
    {
        return 0;
    }

    template <class T, class C>
    operator T C::*() const
    {
        return 0;
    }
private:
    void operator&() const;
} u_nullptr = {};

namespace ft
{
    // to_string
    // 어떤 Data type이 와도 string으로 바꿔줍니다
    // http://www.cplusplus.com/articles/D9j2Nwbp/
    template <typename T>
    std::string to_string(T n)
    {
        std::ostringstream os;
        os << n;
        return (os.str());
    };
    
    // <functional>
    // binary_function
    // http://www.cplusplus.com/reference/functional/binary_function/
    // less를 구한하기 위한 base struct
    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1   first_argument_type;
        typedef Arg2   second_argument_type;
        typedef Result result_type;
    };

    // <functional>
    // less 구조체
    // https://docs.microsoft.com/ko-kr/cpp/standard-library/less-struct?view=msvc-170
    // 함수 객체 개념을 알아봅시다.
    template <class Type = void>
    struct less : public binary_function <Type, Type, bool>
    {
        bool operator()(const Type& Left, const Type& Right) const;
    };

    // <utility>
    // std::pair struct
    // https://en.cppreference.com/w/cpp/utility/pair
    template <class T1, class T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        T1 first;
        T2 second;

        pair() : first(), second() {}
        pair(T1 const& t1, T2 const& t2) : first(t1), second(t2) {}
        pair(const pair<T1, T2>& p) : first(p.first), second(p.second) {}
        pair& operator=(pair const& p) {
            first = p.first;
            second = p.second;
            return *this;
        }

    };
    template <class T1, class T2>
    inline
    bool
    operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return x.first == y.first && x.second == y.second;
    }
    template <class T1, class T2>
    inline
    bool
    operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(x == y);
    }
    template <class T1, class T2>
    inline
    bool
    operator<(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
    }
    template <class T1, class T2>
    inline
    bool
    operator>(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return y < x;
    }
    template <class T1, class T2>
    inline
    bool
    operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(x < y);
    }
    template <class T1, class T2>
    inline
    bool
    operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
    {
        return !(y > x);
    }
    template <class T1, class T2>
    inline
    ft::pair<T1,T2>
    make_pair(T1 x, T2 y)
    {
        return ft::pair<T1, T2>(x, y);
    }

    // enable_if
    template<bool B, class T = void>
    struct enable_if {};

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    // <type_traits>
    // is_integral
    template <bool is_integral, typename T>
    struct is_integral_res
    {
        typedef T   type;
        static const bool value = is_integral;
    };
    // template specialization
    template <typename T>
    struct is_integral_type : public is_integral_res<false, bool> {};
    template <>
    struct is_integral_type<bool> : public is_integral_res<true, bool> {};
    template <>
    struct is_integral_type<char> : public is_integral_res<true, char> {};
    template <>
    struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
    template <>
    struct is_integral_type<short int> : public is_integral_res<true, short int> {};
    template <>
    struct is_integral_type<int> : public is_integral_res<true, int> {};
    template <>
    struct is_integral_type<long int> : public is_integral_res<true, long int> {};
    template <>
    struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
    template <>
    struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
    template <>
    struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
    template <>
    struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
    template <>
    struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
    template <>
    struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};
    // is_integral
    template <typename T>
    struct is_integral : public is_integral_type<T> {};

    // iterator
    class random_access_iterator_tag {};
    class bidirectional_iterator_tag {};
    class forward_iterator_tag {};
    class input_iterator_tag {};
    class output_iterator_tag {};

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
    struct is_input_iterator_tagged<ft::random_access_iterator_tag>
        : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
        : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::forward_iterator_tag>
        : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};
    template <>
    struct is_input_iterator_tagged<ft::input_iterator_tag>
        : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};

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
    class InvalidIteratorException : public std::exception
    {
    public:
        virtual const char * what() const throw()
        {
            return "Is invalid iterator tag : ";
        }
    };
    
    // iterator_traits
    template<class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template<class T>
    struct iterator_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };

    template<class T>
    struct iterator_traits<const T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ft::random_access_iterator_tag iterator_category;
    };
    
    // std::distance
    template<class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
    distance (InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type ret = 0;
        while (first != last)
        {
            first++;
            ret++;
        }
        return ret;
    }

    // base iterator
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator
    {
    public:
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
        typedef Category    iterator_category;
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

    // lexcicographical_compare
    // https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
    // https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
    // 위 reference에 코드가 다 나와있다.
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2) return true;
            if (*first2 < *first1) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                InputIt2 first2, InputIt2 last2,
                                Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (comp(*first1, *first2)) return true;
            if (comp(*first2, *first1)) return false;
        }
        return (first1 == last1) && (first2 != last2);
    }
    
}

#endif
